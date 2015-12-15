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
    widgetFactory = new PMFactory;)" },
    { "Explain the BUILDER design pattern.",
        R"(
Separates the construction of a complex object from its representation so that
the same construction process can create different representations.

The example presented in the book illustrates how a generic representation of a
formatted text document is converted to various specialized formats (e.g. ASCII,
TeX, etc).

  class MazeBuilder {
  public:
    virtual void BuildMaze() {}
    virtual void BuildRoom(int room) {}
    virtual void BuildDoor(int roomFrom, int roomTo) {}
    virtual Maze *GetMaze() { return nullptr; }
  protected:
    MazeBuilder();
  };
  
  class StandardMazeBuilder : public MazeBuilder { ...
  class ExoticMazeBuilder : public MazeBuilder { ...
  
  Maze *MazeGame::CreateMaze(MazeBuilder &builder) {
    builder.BuildMaze();
    builder.BuildRoom(1);
    builder.BuildRoom(2);
    builder.BuildDoor(1, 2);
    return builder.GetMaze();
  }
  
  Maze *MazeGame::CreateComplexMaze(MazeBuilder &builder) {
    builder.BuildMaze();
    builder.BuildRoom(1);
    // ...
    builder.BuildRoom(1001);
    return builder.GetMaze();
  })" },
    { "What's the difference between the ABSTRACT FACTORY and BUILDER design patterns?",
        R"(
The ABSTRACT FACTORY pattern provides a factory for creating components of a
product.  The client of the factory obtains concrete components from the factory
through member function calls (e.g. createWindow, createScrollBar) and assembles
them together.  The factory is not responsible for assembling the final product,
it's just responsible for creating components.

The BUILDER pattern also facilitates building a product, but unlike the ABSTRACT
FACTORY, the builder is responsible for building a concrete version of the
final product.  The client builds the product by calling a set of member
functions that make logical (abstract) changes to the product.  Once all of the
changes have been made, the final concrete product can be obtained through a
call to another member function (e.g. getProduct).
)" },
  };

}

#endif // quiz_design_patterns_hpp
