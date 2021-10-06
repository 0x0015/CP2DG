#include "FunctionalGameObject.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"

template<typename T> void FunctionalGameObject<T>::Initialize(){
	for(int i=0;i<InitializeList.size();i++){
		InitializeList[i](this);
	}
	T::Initialize();
}

template<typename T> void FunctionalGameObject<T>::Load(){
	for(int i=0;i<LoadList.size();i++){
		LoadList[i](this);
	}
	T::Load();
}

template<typename T> void FunctionalGameObject<T>::Draw(){
	for(int i=0;i<DrawList.size();i++){
		DrawList[i](this);
	}
	T::Draw();
}

template<typename T> void FunctionalGameObject<T>::Update(){
	for(int i=0;i<UpdateList.size();i++){
		UpdateList[i](this);
	}
	T::Update();
}

template<typename T> FunctionalGameObject<T>::FunctionalGameObject(){
	for(int i=0;i<ConstructorList.size();i++){
		ConstructorList[i](this);
	}
}

template<typename T> FunctionalGameObject<T>::~FunctionalGameObject(){
	for(int i=0;i<DeconstructorList.size();i++){
		DeconstructorList[i](this);
	}
}

template class FunctionalGameObject<GameObject>;
template class FunctionalGameObject<Sprite>;
