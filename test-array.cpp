#pragma once

#include "array.h" 


void FAIL() { printf("Failed\n");  exit(1); }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }

// test equal
void test1() {
    String* s = new String("Hello");
    Array* a = new Array();
    Array* b = new Array();
    a->add(s);
    b->add(s);
    t_true(a->equals(a));
    t_true(b->equals(b));
    t_true(a->equals(b));
}

// test length, add, set, remove
void test2() {
    String* s = new String("Hello");
    String* t = new String("World");
    String* u = s->concat(t);
    Array* a = new Array();
    t_true(a->length() == 0);
    a->add(s);
    a->add(t);
    a->add(t);
    a->set(2, u);
    t_true(a->get(2)->equals(u));
    t_true(a->length() == 3);
    a->remove(2);
    t_true(a->length() == 2);
    t_true(a->get(1)->equals(t));
}

// test hash_me
void test3() {
    String* s = new String("Hello");
    Array* a = new Array();
    a->add(s);
    t_true(a->hash() == a->hash());
}

// test append, get
void test4() {
    String* s = new String("Hello");
    String* t = new String("World");
    String* u = s->concat(t);
    Array* a = new Array();
    a->add(s);
    Array* b = new Array();
    b->add(t);
    b->add(u);
    Array* c = a->append(b);
    t_true(c->length() == 3);
    t_true(c->get(2)->equals(u));
}

// test index_of, clear
void test5() {
    String* s = new String("Hello");
    String* t = new String("World");
    String* u = s->concat(t);
    Array* a = new Array();
    a->add(s);
    a->add(t);
    a->add(u);
    t_true(a->index_of(s) == 0);
    t_true(a->index_of(u) == 2);
    t_true(a->get(2)->equals(u));
    a->clear();
    t_true(a->length() == 0);
}

// test equal for different arrays
void test6() {
    String* s = new String("Hello");
    Array* a = new Array();
    StrArray* b = new StrArray();
    IntArray* c = new IntArray();
    a->add(s);
    b->add(s);
    t_true(a->equals(b));
    t_true(a->hash() == b->hash());
    t_false(c->equals(a));
    t_false(a->hash() == c->hash());
}

// test length, add, set, remove for bool array
void test7() {
    BoolArray* a = new BoolArray();
    t_true(a->length() == 0);
    a->add(false);
    a->add(false);
    a->set(1, true);
    t_true(a->get(1)->getValue());
    t_true(a->length() == 2);
    a->remove(1);
    t_true(a->length() == 1);
    t_false(a->get(0)->getValue());
}

// test append, get for float array
void test8() {
    FloatArray* a = new FloatArray();
    a->add(1.3f);
    FloatArray* b = new FloatArray();
    b->add(2.3f);
    b->add(3.3f);
    FloatArray* c = a->append(b);
    t_true(c->length() == 3);
    t_true(c->get(2)->getValue() == 3.3f);
}

// test index_of, clear for int array
void test9() {
    IntArray* a = new IntArray();
    Integer* one = new Integer(1);
    Integer* two = new Integer(2);
    Integer* three = new Integer(3);
    a->add(one);
    a->add(two);
    a->add(three);
    t_true(a->index_of(one) == 0);
    t_true(a->index_of(two) == 1);
    t_true(a->get(2)->equals(three));
    a->clear();
    t_true(a->length() == 0);
}

// make all tests run
int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    return 0;
}