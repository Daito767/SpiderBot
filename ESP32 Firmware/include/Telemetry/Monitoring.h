#ifndef MONITORING_H
#define MONITORING_H

class Monitoring {
public:
	Monitoring();
	void update();

private:
	void checkMemoryUsage();
	void checkRSSI();
};

#endif