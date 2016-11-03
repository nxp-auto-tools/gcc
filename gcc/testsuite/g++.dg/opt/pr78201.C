// PR middle-end/78201
// { dg-do compile }
// { dg-options "-O2" }

struct B { long d (); } *c;
long e;

void f() {
    char a[e] = "";
      c && c->d();
}
