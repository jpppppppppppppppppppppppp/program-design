#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>
#include <cstdio>
struct problemtype{
	std::string statue;
	std::string condition;
	int peTime=0;
	int tryTimes=0;
	int AcTime=0;
	int WATime=0;
	int RETime=0;
	int TLETime=0;
	int passtime=0;
	friend bool operator < (const problemtype &lhs,const problemtype &rhs){
		if(lhs.tryTimes!=rhs.tryTimes)return lhs.tryTimes > rhs.tryTimes;
		return lhs.AcTime > rhs. AcTime;
	}
};
void write(const char *f,int len){
	auto p=f;
	for(int i=0;i<len;i++){
		putchar(*p);
		p++;
	}
	puts("");
}
struct team{
	int num;
	std::string name;
	int rank=0;
	int pass=0;
	int sum=0;
	std::unordered_map<int,problemtype>problemList;
	int peTimes[30]{0};
	int done=0;
	int acdone=0;
	int wadone=0;
	int redone=0;
	int tledone=0;
	friend bool operator < (const team &lhs, const team &rhs){

		if(lhs.pass!=rhs.pass)return lhs.pass>rhs.pass;
		else{
			if(lhs.sum!=rhs.sum)return lhs.sum<rhs.sum;
			else{
				for(int i = 0; i < lhs.num; i++){
					if(lhs.peTimes[i] != rhs.peTimes[i])return lhs.peTimes[i] < rhs.peTimes[i];
				}
				return lhs.name < rhs.name;
			}
		}
	}
};

bool cmp(const std::pair<std::string,team>&lhs,const std::pair<std::string,team>&rhs){
	return lhs.second < rhs.second;
};

void update(team &t){
	std::sort(t.peTimes,t.peTimes+30,std::greater<>());
//	std::cout << t.peTimes.size() << std::endl;
//	std::cout << vt.size() << std::endl;
}//更新总罚时排名

void flush(std::unordered_map<std::string, team> &m,std::vector<std::string>&rank,std::set<team>&s){
	int temp_rank=1;
	for(auto i=s.begin();i!=s.end();i++){
		rank[temp_rank-1]=i->name;
		m[i->name].rank = temp_rank++;
	}
}//更新榜单

void reflush(std::unordered_map<std::string, team> &m,std::vector<std::string>&rank,std::set<team>&team_set,std::unordered_map<std::string,std::vector<problemtype>>&freezing) {
	team_set.clear();
	for(auto it: m)team_set.insert(it.second);
	auto last_iter = team_set.end();
	last_iter--;
	while (last_iter != team_set.begin()) {
		auto original_next = ++last_iter;
		--last_iter;
		if(freezing.find(last_iter->name) == freezing.end()) {
			--last_iter;
			continue;
		}
		auto delete_iter = last_iter;
		std::string name = last_iter->name;
		if(freezing[name].empty()) {
			freezing.erase(name);
			continue;
		}
		team &insert_iter = m[name];
		const auto pro = freezing[name][freezing[name].size() - 1];
		freezing[name].pop_back();

		if(pro.statue == "Accepted") {
			insert_iter.peTimes[insert_iter.pass] = pro.peTime;
			insert_iter.pass++;
			insert_iter.problemList[pro.tryTimes].passtime = pro.peTime;
			insert_iter.problemList[pro.tryTimes].peTime = 20 * insert_iter.problemList[pro.tryTimes].tryTimes + pro.peTime;
			std::sort(insert_iter.peTimes, insert_iter.peTimes + 30, std::greater<>());
			insert_iter.sum += insert_iter.problemList[pro.tryTimes].peTime;
		}
		else if(pro.statue != "pass") {
			insert_iter.problemList[pro.tryTimes].tryTimes++;
		}
		else continue;
		team_set.erase(delete_iter);
		insert_iter = m[name];
		auto new_next = ++team_set.insert(insert_iter).first;
		if(new_next != original_next) {
			std::cout << insert_iter.name << " " << new_next->name << " "
			          << insert_iter.pass << " "
			          << insert_iter.sum << std::endl;
		}
		--original_next;
		last_iter = original_next;
	}
	while (freezing.find(last_iter->name) != freezing.end()) {
		std::string name = last_iter->name;
		if(freezing[name].empty()) {
			freezing.erase(name);
		}
		else {
			team &insert_iter = m[name];
			const auto pro = freezing[name][freezing[name].size() - 1];
			freezing[name].pop_back();
			if(pro.statue == "Accepted") {
				insert_iter.peTimes[insert_iter.pass] = pro.peTime;
				insert_iter.pass++;
				insert_iter.problemList[pro.tryTimes].passtime = pro.peTime;
				insert_iter.problemList[pro.tryTimes].peTime = 20 * insert_iter.problemList[pro.tryTimes].tryTimes + pro.peTime;
				std::sort(insert_iter.peTimes, insert_iter.peTimes + 30, std::greater<>());
				insert_iter.sum += insert_iter.problemList[pro.tryTimes].peTime;
			}
			else if(pro.statue != "pass") {
				insert_iter.problemList[pro.tryTimes].tryTimes++;
			}
		}

	}
	int temp_rank = 1;
	team_set.clear();
	for(const auto &iter: m) {
		team_set.insert(iter.second);
	}
	for(auto iter = team_set.begin(); iter != team_set.end(); iter++) {
		m[iter->name].rank = temp_rank;
		rank[temp_rank - 1] = m[iter->name].name;
		temp_rank++;
	}
}
std::set<team>s;
std::unordered_map<std::string, team>m;
std::vector<std::string>rank;
std::unordered_map<std::string,std::vector<problemtype>>freezing;
bool NotStart = true;
bool NotFreeze = true;
int duration_time = 0, problem = 0;
int main() {
//	freopen("13.in", "r", stdin);
//	freopen("ans.txt","w",stdout);
	std::ios::sync_with_stdio();
	std::string command;
	while (getline(std::cin, command) and command != "END") {
		std::istringstream iss;
		iss.str(command);
		std::string mode;
		iss >> mode;
		if(mode == "START") {
			if(NotStart) {
				for(int i = 0; i < m.size(); i++)rank.push_back("");
				for(auto i: m)s.insert(i.second);
				flush(m, rank, s);
				NotStart = false;
				std::string meiyongdehua;
				iss >> meiyongdehua;
				iss >> duration_time;
				iss >> meiyongdehua;
				iss >> problem;
				write("[Info]Competition starts.", 25);
				continue;
			}
			else write("[Error]Start failed: competition has started.", 45);
		}
		else if(mode == "ADDTEAM") {
			if(!NotStart) {
				std::cout << "[Error]Add failed: competition has started." << std::endl;
				continue;
			}
			else {
				std::string name;
				iss >> name;
				if(m.find(name) != m.end())write("[Error]Add failed: duplicated team name.", 40);
				else {
					team t = {30, name};
					m.insert(std::pair<std::string, team>(name, t));
					write("[Info]Add successfully.", 23);
				}
			}
		}
		else if(mode == "SUBMIT") {


			char problemName;
			std::string meiyongdehua;
			iss >> problemName;
			int problemNum = problemName - 'A' + 1;
			iss >> meiyongdehua;
			std::string name;
			iss >> name;
			iss >> meiyongdehua;
			std::string statue;
			iss >> statue;
			iss >> meiyongdehua;
			int time;
			iss >> time;
			team &t = m[name];
			t.done = problemNum;

			if(m.find(name) != m.end() and t.problemList.find(problemNum) != t.problemList.end() and
			   t.problemList[problemNum].AcTime > 0) {
				t.done = problemNum;
				t.problemList[problemNum].condition = statue;
				if(statue == "Accepted") {
					t.problemList[problemNum].AcTime = time, t.acdone = problemNum;
					if(t.problemList[problemNum].passtime == 0)t.problemList[problemNum].passtime = time;
				}
				if(statue == "Wrong_Answer")t.problemList[problemNum].WATime = time, t.wadone = problemNum;
				if(statue == "Runtime_Error")t.problemList[problemNum].RETime = time, t.redone = problemNum;
				if(statue == "Time_Limit_Exceed")t.problemList[problemNum].TLETime = time, t.tledone = problemNum;
				if(!NotFreeze and t.problemList[problemNum].peTime == 0) {
					if(freezing.find(name) == freezing.end()) {
						problemtype pro = {"pass", "pass", 0, problemNum};
						std::vector<problemtype> vp;
						vp.push_back(pro);
						freezing.insert(std::make_pair(name, vp));
					}
					else {
						problemtype pro = {"pass", "pass", 0, problemNum};
						freezing[name].push_back(pro);
					}
				}

				continue;
			}

			if(NotFreeze) {
				s.erase(t);
				if(statue == "Accepted") {
					t.acdone = problemNum;
					t.pass++;
					if(t.problemList.find(problemNum) == t.problemList.end())
						t.problemList.insert(
							std::pair<int, problemtype>(problemNum, {"Accepted", "Accepted", time, 0, time}));
					else {
						t.problemList[problemNum].peTime = 20 * t.problemList[problemNum].tryTimes + time;
						t.problemList[problemNum].statue = "Accepted";
						t.problemList[problemNum].AcTime = time;
					}
					t.peTimes[t.pass - 1] = time;
					t.sum += t.problemList[problemNum].peTime;
					if(t.problemList[problemNum].passtime == 0)t.problemList[problemNum].passtime = time;
					update(t);
				}
				else {
					if(t.problemList.find(problemNum) == t.problemList.end())
						t.problemList.insert(std::pair<int, problemtype>(problemNum, {statue, statue, 0, 1}));
					else {
						t.problemList[problemNum].tryTimes++;
					}
					if(statue == "Wrong_Answer")t.problemList[problemNum].WATime = time, t.wadone = problemNum;
					if(statue == "Runtime_Error")t.problemList[problemNum].RETime = time, t.redone = problemNum;
					if(statue == "Time_Limit_Exceed")t.problemList[problemNum].TLETime = time, t.tledone = problemNum;
				}

				t.problemList[problemNum].condition = statue;
				s.insert(t);
			}
			else {
				if(freezing.find(name) == freezing.end()) {
					std::vector<problemtype> vp;
					problemtype pro = {statue, statue, time, problemNum, 1};
					vp.push_back(pro);
					freezing.insert(std::pair<std::string, std::vector<problemtype>>(name, vp));
				}
				else {
					problemtype pro = {statue, statue, time, problemNum, static_cast<int>(freezing[name].size() + 1)};
					freezing[name].push_back(pro);
				}
				t.problemList[problemNum].condition = statue;
				if(statue == "Accepted")t.problemList[problemNum].AcTime = time, t.acdone = problemNum;
				if(statue == "Wrong_Answer")t.problemList[problemNum].WATime = time, t.wadone = problemNum;
				if(statue == "Runtime_Error")t.problemList[problemNum].RETime = time, t.redone = problemNum;
				if(statue == "Time_Limit_Exceed")t.problemList[problemNum].TLETime = time, t.tledone = problemNum;
			}
		}
		else if(mode == "FLUSH") {
			flush(m, rank, s);
			write("[Info]Flush scoreboard.", 23);
		}
		else if(mode == "FREEZE") {
			if(NotFreeze) {
				NotFreeze = false;
				write("[Info]Freeze scoreboard.", 24);
			}
			else write("[Error]Freeze failed: scoreboard has been frozen.", 49);
		}
		else if(mode == "SCROLL") {
			if(NotFreeze)write("[Error]Scroll failed: scoreboard has not been frozen.", 53);
			else {
				write("[Info]Scroll scoreboard.", 24);
				flush(m, rank, s);
				for(int i = 0; i < rank.size(); i++) {
					std::cout << rank[i] << " " << i + 1 << " " << m[rank[i]].pass << " " << m[rank[i]].sum;
					for(int j = 1; j <= problem; j++) {
						std::cout << " ";
						int flag = 0;
						if(freezing.find(rank[i]) != freezing.end()) {
							for(auto iter = freezing[rank[i]].begin(); iter != freezing[rank[i]].end(); iter++)
								if(iter->tryTimes == j)flag++;
						}
						if(flag != 0) {
							if(m[rank[i]].problemList[j].tryTimes == 0)std::cout << "0/" << flag;
							else std::cout << "-" << m[rank[i]].problemList[j].tryTimes << "/" << flag;
						}
						else {
							if(m[rank[i]].problemList[j].peTime > 0) {
								std::cout << "+";
								if(m[rank[i]].problemList[j].tryTimes != 0)std::cout << m[rank[i]].problemList[j].tryTimes;
							}
							else {
								if(m[rank[i]].problemList[j].tryTimes == 0)std::cout << ".";
								else std::cout << "-" << m[rank[i]].problemList[j].tryTimes;
							}
						}
					}
					puts("");
				}
				for(int i = 0; i < m.size(); i++) {
					if(freezing.find(rank[i]) != freezing.end()) {
						std::sort(freezing[rank[i]].begin(), freezing[rank[i]].end());
					}
				}
				if(!freezing.empty()) reflush(m, rank, s, freezing);

				//排名的改变
				for(int i = 0; i < rank.size(); i++) {
					std::cout << rank[i] << " " << i + 1 << " " << m[rank[i]].pass << " " << m[rank[i]].sum;
					for(int j = 1; j <= problem; j++) {
						std::cout << " ";
						if(m[rank[i]].problemList[j].AcTime > 0) {
							std::cout << "+";
							if(m[rank[i]].problemList[j].tryTimes != 0)std::cout << m[rank[i]].problemList[j].tryTimes;
						}
						else {
							if(m[rank[i]].problemList[j].tryTimes == 0)std::cout << ".";
							else std::cout << "-" << m[rank[i]].problemList[j].tryTimes;
						}
					}
					puts("");
				}

				NotFreeze = true;
			}
		}
		else if(mode == "QUERY_SUBMISSION") {
			bool flag = true;
			std::string name, statue, meiyongdehua;
			char problemName;
			int problemNum;
			iss >> name;
			iss >> meiyongdehua;
			iss >> meiyongdehua;
			if(meiyongdehua.length() == 11)flag = false;
			problemName = meiyongdehua[8];
			problemNum = problemName - 'A' + 1;
			iss >> meiyongdehua;
			iss >> meiyongdehua;
			if(meiyongdehua[8] == 'L')statue = "ALL";
			if(meiyongdehua[8] == 'c')statue = "AC";
			if(meiyongdehua[8] == 'r')statue = "WA";
			if(meiyongdehua[8] == 'u')statue = "RE";
			if(meiyongdehua[8] == 'i')statue = "TLE";
			if(m.find(name) == m.end())write("[Error]Query submission failed: cannot find the team.", 53);
			else {
				team &t = m[name];
				write("[Info]Complete query submission.", 32);
				if(flag) {
					if(t.problemList.find(problemNum) == t.problemList.end()) {
						write("Cannot find any submission.", 27);
						continue;
					}
					else {
						if(statue == "ALL") {
							if(t.problemList[problemNum].condition.empty())
								write("Cannot find any submission.", 27);
							else {
								if(t.problemList[problemNum].condition == "Accepted")
									std::cout << name << " " << problemName << " "
									          << t.problemList[problemNum].condition << " "
									          << t.problemList[problemNum].AcTime << std::endl;
								if(t.problemList[problemNum].condition == "Wrong_Answer")
									std::cout << name << " " << problemName << " "
									          << t.problemList[problemNum].condition << " "
									          << t.problemList[problemNum].WATime << std::endl;
								if(t.problemList[problemNum].condition == "Runtime_Error")
									std::cout << name << " " << problemName << " "
									          << t.problemList[problemNum].condition << " "
									          << t.problemList[problemNum].RETime << std::endl;
								if(t.problemList[problemNum].condition == "Time_Limit_Exceed")
									std::cout << name << " " << problemName << " "
									          << t.problemList[problemNum].condition << " "
									          << t.problemList[problemNum].TLETime << std::endl;
							}
						}
						else if(statue == "AC") {
							if(t.problemList[problemNum].AcTime == 0)
								write("Cannot find any submission.", 27);
							else
								std::cout << name << " " << problemName << " Accepted "
								          << t.problemList[problemNum].AcTime << std::endl;
						}
						else if(statue == "WA") {
							if(t.problemList[problemNum].WATime == 0)
								write("Cannot find any submission.", 27);
							else
								std::cout << name << " " << problemName << " Wrong_Answer "
								          << t.problemList[problemNum].WATime << std::endl;
						}
						else if(statue == "RE") {
							if(t.problemList[problemNum].RETime == 0)
								write("Cannot find any submission.", 27);
							else
								std::cout << name << " " << problemName << " Runtime_Error "
								          << t.problemList[problemNum].RETime << std::endl;
						}
						else if(statue == "TLE") {
							if(t.problemList[problemNum].TLETime == 0)
								write("Cannot find any submission.", 27);
							else
								std::cout << name << " " << problemName << " Time_Limit_Exceed "
								          << t.problemList[problemNum].TLETime << std::endl;
						}
					}

				}
				else {
					if(statue == "ALL") {
						problemNum = t.done;
						problemName = 'A' + problemNum - 1;
						if(t.problemList.find(problemNum) == t.problemList.end()) {
							write("Cannot find any submission.", 27);
							continue;
						}
						if(t.problemList[problemNum].condition.empty())
							write("Cannot find any submission.", 27);
						else {
							if(t.problemList[problemNum].condition == "Accepted")
								std::cout << name << " " << problemName << " "
								          << t.problemList[problemNum].condition << " "
								          << t.problemList[problemNum].AcTime << std::endl;
							if(t.problemList[problemNum].condition == "Wrong_Answer")
								std::cout << name << " " << problemName << " "
								          << t.problemList[problemNum].condition << " "
								          << t.problemList[problemNum].WATime << std::endl;
							if(t.problemList[problemNum].condition == "Runtime_Error")
								std::cout << name << " " << problemName << " "
								          << t.problemList[problemNum].condition << " "
								          << t.problemList[problemNum].RETime << std::endl;
							if(t.problemList[problemNum].condition == "Time_Limit_Exceed")
								std::cout << name << " " << problemName << " "
								          << t.problemList[problemNum].condition << " "
								          << t.problemList[problemNum].TLETime << std::endl;
						}
					}
					else if(statue == "AC") {
						problemNum = t.acdone;
						problemName = 'A' + problemNum - 1;
						if(t.problemList.find(problemNum) == t.problemList.end()) {
							write("Cannot find any submission.", 27);
							continue;
						}
						if(t.problemList[problemNum].AcTime == 0)
							write("Cannot find any submission.", 27);
						else
							std::cout << name << " " << problemName << " Accepted "
							          << t.problemList[problemNum].AcTime << std::endl;
					}
					else if(statue == "WA") {
						problemNum = t.wadone;
						problemName = 'A' + problemNum - 1;
						if(t.problemList.find(problemNum) == t.problemList.end()) {
							write("Cannot find any submission.", 27);
							continue;
						}
						if(t.problemList[problemNum].WATime == 0)
							write("Cannot find any submission.", 27);
						else
							std::cout << name << " " << problemName << " Wrong_Answer "
							          << t.problemList[problemNum].WATime << std::endl;
					}
					else if(statue == "RE") {
						problemNum = t.redone;
						problemName = 'A' + problemNum - 1;
						if(t.problemList.find(problemNum) == t.problemList.end()) {
							write("Cannot find any submission.", 27);
							continue;
						}
						if(t.problemList[problemNum].RETime == 0)
							write("Cannot find any submission.", 27);
						else
							std::cout << name << " " << problemName << " Runtime_Error "
							          << t.problemList[problemNum].RETime << std::endl;
					}
					else if(statue == "TLE") {
						problemNum = t.tledone;
						problemName = 'A' + problemNum - 1;
						if(t.problemList.find(problemNum) == t.problemList.end()) {
							write("Cannot find any submission.", 27);
							continue;
						}
						if(t.problemList[problemNum].TLETime == 0)
							write("Cannot find any submission.", 27);
						else
							std::cout << name << " " << problemName << " Time_Limit_Exceed "
							          << t.problemList[problemNum].TLETime << std::endl;
					}
				}
			}
		}
		else if(mode == "QUERY_RANKING") {
			std::string name;
			iss >> name;
			if(m.find(name) == m.end())write("[Error]Query ranking failed: cannot find the team.", 50);
			else {
				std::cout << "[Info]Complete query ranking." << std::endl;
				if(!NotFreeze)
					write("[Warning]Scoreboard is frozen. The ranking may be inaccurate until it were scrolled.", 84);
				std::cout << name << " NOW AT RANKING " << m[name].rank << std::endl;
			}
		}
	}
	write("[Info]Competition ends.", 23);
	return 0;
}