/*
 *  Archiving code example from the tutorial
 */

#include <fstream>

#ifdef IN_GINAC
#include "ginac.h"
#else
#include <ginac/ginac.h>
#endif
using namespace std;
using namespace GiNaC;

int main()
{
	symbol x("x"), y("y"), z("z");

	// do some math
	
	ex foo = sin(x + 2*y) + 3*z + 41;
	ex bar = foo + 1;

	// write the archive
	
	archive a;
	a.archive_ex(foo, "foo");
	a.archive_ex(bar, "the second one");

	ofstream out("foobar.gar");
	out << a;
	out.close();

	// read in the archive
	
	archive a2;
	ifstream in("foobar.gar");
	in >> a2;

	lst syms = {x, y};

	ex ex1 = a2.unarchive_ex("foo");
	ex ex2 = a2.unarchive_ex("the second one");

	// do some math again
	
	cout << ex1 << endl;              // prints "41+sin(x+2*y)+3*z"
	cout << ex2 << endl;              // prints "42+sin(x+2*y)+3*z"
	cout << ex1.subs(x == 2) << endl; // prints "41+sin(2+2*y)+3*z"
}

