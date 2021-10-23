#include <iostream>
#include <functional>
#include <vector>

template<typename T> class FunctionalGameObject : public T{
	void Initialize();
	std::vector<std::function<void(T*)>> InitializeList;
	void Load();
	std::vector<std::function<void(T*)>> LoadList;
	void Draw();
	std::vector<std::function<void(T*)>> DrawList;
	void Update();
	std::vector<std::function<void(T*)>> UpdateList;
	FunctionalGameObject();
	std::vector<std::function<void(T*)>> ConstructorList;
	~FunctionalGameObject();
	std::vector<std::function<void(T*)>> DeconstructorList;
};
