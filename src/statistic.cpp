#include "statistic.h"
#include "config.h"

int       Statistic::score_;
TimePoint Statistic::start_time_;
Seconds   Statistic::time_passed_;

void Statistic::addScore(int points) { score_ += points; }

int Statistic::getScore() { return score_; }

void Statistic::updateTime(TimePoint current_time) {
  time_passed_ = current_time - start_time_;
}

Seconds Statistic::getTimePassed() { return time_passed_; }

void Statistic::resetStatistics() {
  score_       = 0;
  start_time_  = Clock::now();
  time_passed_ = Seconds(0);
}