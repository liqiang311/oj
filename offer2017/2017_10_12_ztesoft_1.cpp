#include <iostream>
using namespace std;

class Package
{
private:
	int baseMoney;
	int baseFlow;
	int baseTime;
	int moneyPerMB;
	int moneyPerMin;

	int FlowMoney(int flow)
	{
		if (flow <= baseFlow) return 0.0;
		return (flow - baseFlow + 999) / 1000 * moneyPerMB;
	}
	int TimeMoney(int time)
	{
		if (time <= baseTime) return 0.0;
		return (time - baseTime + 59) / 60 * moneyPerMin;
	}
public:
	Package(int baseMoney, int baseFlow, int baseTime, int moneyPerMB, int moneyPerMin)
	{
		this->baseMoney = baseMoney;
		this->baseFlow = baseFlow;
		this->baseTime = baseTime;
		this->moneyPerMB = moneyPerMB;
		this->moneyPerMin = moneyPerMin;
	}
	int Money(int flow, int time)
	{
		return baseMoney + FlowMoney(flow) + TimeMoney(time);
	}
};

int main()
{
	Package p(5900,500*1000,100*60,30,15);
	cout<<p.Money(500*1000,100*60)<<endl;
	cout<<p.Money(500*1000+1,100*60+1)<<endl;
	cout<<p.Money(500*1000+999,100*60+59)<<endl;

    getchar();
	return 0;
}
