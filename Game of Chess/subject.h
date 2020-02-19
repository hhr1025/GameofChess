#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>


// DO NOT MODIFY THIS FILE!

template <typename StateType> class Observer;

template < typename StateType> class Subject {
  std::vector<Observer< StateType>*> observers;
  StateType state;
 public:
  void setState(StateType newS);
  void attach(Observer<StateType> *o);  
  void detachobservers();
  void notifyObservers();
  StateType getState() const;
};

template < typename StateType>
void Subject<StateType>::attach(Observer<StateType> *o) {
   observers.emplace_back(o);
}

template < typename StateType>
void Subject<StateType>::detachobservers() {
  observers.clear();
}

template <typename StateType>
void Subject<StateType>::notifyObservers() {
  for (auto &ob : observers){
     ob->notify(*this);
  }
}

template < typename StateType>
void Subject<StateType>::setState(StateType newS) { state = newS; }

template <typename StateType>
StateType Subject<StateType>::getState() const { return state; }
#endif

