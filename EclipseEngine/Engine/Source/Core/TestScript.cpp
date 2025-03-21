#include "TestScript.hpp"
#include <iostream>

namespace Core
{
	TestScript::~TestScript() {};

	void TestScript::Awake()
	{
		std::cout << "Awake" << std::endl;
	}

	void TestScript::OnEnable()
	{
		std::cout << "OnEnable" << std::endl;
	}

	void TestScript::Start()
	{
		std::cout << "Start" << std::endl;
	}

	void TestScript::Update()
	{
		std::cout << "Update" << std::endl;
	}

	void TestScript::OnDisable()
	{
		std::cout << "OnDisable" << std::endl;
	}

	void TestScript::OnDestroy()
	{
		std::cout << "OnDestroy" << std::endl;
	}


}