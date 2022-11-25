#include "header/moveStation.h"

stack<Station*> session;
stack<Station*> visit;
int check = 0;

bool goNext(Station*& tmp)
{
	if (check)
	{
		check = 0;
		tmp = tmp->ptr[2]->next;
		return true;
	}
	if (tmp->flag == 1 && !visit.empty())
	{
		if (tmp->ptr[1]->next == visit.top())
		{
			tmp = tmp->ptr[2]->next;
			visit.pop();
			return true;
		}
	}
	if (tmp->transfer && tmp->ptr.size() == 2)
		tmp = tmp->ptr[0]->next;
	else if (tmp->ptr.size() == 1 && tmp->flag != 4)
		tmp = tmp->ptr[0]->next;
	else if (tmp->flag == 1)
	{
		session.push(tmp);
		tmp = tmp->ptr[1]->next;
		visit.push(tmp);
	}

	else if (tmp->flag == 4)
	{
		tmp = session.top(); session.pop();
		tmp = tmp->ptr[2]->next;
	}
	else if (tmp->flag == 3)
	{
		check = 1;
		tmp = tmp->ptr[1]->next;
	}
	else if (tmp->flag == 2)
	{
		tmp = session.top(); session.pop();
	}

	else if (!tmp->ptr.size() == 1 && session.empty())
		return false;
	else
		tmp = tmp->ptr[1]->next;
	return true;
}

void visitClear()
{
	while (!visit.empty())
		visit.pop();
}