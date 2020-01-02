#ifndef DECISION_HPP
#define DECISION_HPP

enum class Decision : bool { cooperate, defect };

Decision operator!(const Decision &d);

#endif
