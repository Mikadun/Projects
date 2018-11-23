// Copyright 2018 Gribak Jaroslav

#include <map>
#include <string>

using std::string;
using std::map;

class Object {
 public:
    virtual string ToString() const = 0;
};

class TemplateObject : public Object {
 private:
  string name;
 public:
    explicit TemplateObject(string name) { this->name = name; }
    virtual string ToString() const { return name; }
};

struct Functor {
  Object* operator()() {
    if (func == nullptr)
      return new TemplateObject(name);
    else
      return func();
  }

  string name;
  Object* (*func)() = nullptr;
  explicit Functor(const string& name) { this->name = name; }
  explicit Functor(Object* (* const func)()) { this->func = func; }
};

class Factory {
 public:
    Object* Create(const string& class_id);
    Factory();
    void Register(const string &class_id, Object* (*f)());
 private:
    map<string, Functor> reg;
};

Object* Factory::Create(const string& class_id) {
  auto result = reg.find(class_id);
  if (result != reg.end())
    return result->second();
  else
    return nullptr;
}

void Factory::Register(const string &class_id, Object* (*f)()) {
  reg.insert({class_id, Functor(f)});
}

Factory::Factory() {
  string n[] = {"apple!", "list", "yet another identifier"};
  for (int i = 0; i < 3; i++) {
    string s(n[i]);
    reg.insert({s, Functor(s)});
  }
}
