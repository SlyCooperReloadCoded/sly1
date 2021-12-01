#include <xform.h>

#include <cassert>

int main()
{
	EXIT* exit = new EXIT();

	SetExitExits(exit, EXITS::Blocked);
	assert(exit->fKeyed == EXITS::Blocked);

	SetExitExits(exit, EXITS::Disabled);
	assert(exit->fKeyed == EXITS::Disabled);

	SetExitExits(exit, EXITS::Enabled);
	assert(exit->fKeyed == EXITS::Enabled);

	SetExitExits(exit, EXITS::Exiting);
	assert(exit->fKeyed == EXITS::Exiting);

	return 0;
}