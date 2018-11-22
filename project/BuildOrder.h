#pragma once
class BuildOrder
{
public:
    enum GOALTYPE;
    struct goal
    {
        GOALTYPE goalType;
        int probeGoal;
        goal *nextGoal;
    };
    void addEndGoal(GOALTYPE type, int probeGoal);
    void addStartGoal(GOALTYPE type, int probeGoal);
    void completeGoal();
    goal *first, *last;

	BuildOrder();
	~BuildOrder();
};

