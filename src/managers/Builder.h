//============================================================================
// Name       		: Builder.h
// Author     		: Thomas Hooks
// Last Modified	: 02/29/2020
//============================================================================




#ifndef BUILDER_H_
#define BUILDER_H_




template <class BaseType>
class BuilderBase {

public:

	BuilderBase() {}

    virtual ~BuilderBase() {}

    virtual BaseType* build() = 0;
};



template <class DerivedType, class BaseType>
class AbstractBuilder : public BuilderBase<BaseType> {

public:

	AbstractBuilder() {}

	~AbstractBuilder() {}

	BaseType* build() override {
		return new DerivedType;
	}
};



template <class DerivedType>
class EntityBuilder : public AbstractBuilder<DerivedType, class Entity> {

public:

	EntityBuilder() {}

	~EntityBuilder() {}
};


#endif /* BUILDER_H_ */



