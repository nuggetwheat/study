#ifndef quiz_design_patterns_hpp
#define quiz_design_patterns_hpp

#include <initializer_list>

#include "quiz.hpp"

/** [TODO]
 */

namespace study {

  const std::initializer_list<Item> design_patterns {
    { "Explain the ABSTRACT FACTORY design pattern.",
        R"(
Provides an interface for creating families of related or dependent objects
without specifying their concrete classes.

Normally a single instance of a ConcreteFactory class is created at run-time.
This concrete factory creates a family of widget objects having a particular
implementation.  To switch to a different family of widget objects, the client
uses a different concrete factory.

For example:

  class AbstractFactory {
    virtual AbstractWindow createWindow(...) = 0;
    virtual AbstractScrollBar createScrollBar(...) = 0;
  }

  class MotifFactory : public AbstractFactory {
    virtual AbstractWindow createWindow(...) { return MotifWindow; }
    virtual AbstractScrollBar createScrollBar(...) { return MotifScrollBar; }
  }

  class PMFactory : public AbstractFactory {
    virtual AbstractWindow createWindow(...) { return PMWindow; }
    virtual AbstractScrollBar createScrollBar(...) { return PMScrollBar; }
  }

Then the client can select a concrete widget factory based on some configuration
variable:

  AbstractFactory widgetFactory;
  if (style == MOTIF)
    widgetFactory = new MotifFactory;
  else if (style == PM)
    widgetFactory = new PMFactory;)" }
  };

}

#endif // quiz_design_patterns_hpp
