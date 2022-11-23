#include "dataStruct.h"
#include <vector>
#include <string>
#include <stack>

stack<Station*> session;

bool goNext(Station*& tmp)
{
	if (tmp->ptr.size() == 1 && tmp->flag != 4)
		tmp = tmp->ptr[0]->next;
	else if (tmp->flag == 1)
	{
		session.push(tmp);
		tmp = tmp->ptr[1]->next;
	}
	else if (tmp->flag == 4)
	{
		tmp = session.top(); session.pop();
		tmp = tmp->ptr[2]->next;
	}
	else if (!tmp->ptr.size() == 1 && session.empty())
		return false;
	else
		tmp = tmp->ptr[1]->next;
	return true;
}
