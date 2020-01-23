#ifndef DECISION_HPP
#define DECISION_HPP

enum class Decision : unsigned char { cooperate, defect };

Decision operator!(const Decision &d);

#endif
