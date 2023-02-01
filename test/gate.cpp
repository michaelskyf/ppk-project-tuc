#include <gtest/gtest.h>
#include <vector>
#include "../src/gate.cpp"

TEST(gate_cpp, and)
{
	struct
	{
		std::vector<bool> inputs;
		bool expected;
	}
	test_data[]
	{
		{{1,1,1,1}, true},
		{{1,0,1}, false},
		{{0}, false},
		{{1}, true},
		{{0,0,0,0}, false},
	};

	for(const auto& t : test_data)
	{
		EXPECT_EQ(get_value_and(t.inputs), t.expected);
	}
}

TEST(gate_cpp, nand)
{
	struct
	{
		std::vector<bool> inputs;
		bool expected;
	}
	test_data[]
	{
		{{1,1,1,1}, false},
		{{1,0,1}, true},
		{{0}, true},
		{{1}, false},
		{{0,0,0,0}, true},
	};

	for(const auto& t : test_data)
	{
		EXPECT_EQ(get_value_nand(t.inputs), t.expected);
	}
}

TEST(gate_cpp, or)
{
	struct
	{
		std::vector<bool> inputs;
		bool expected;
	}
	test_data[]
	{
		{{1,1,1,1}, true},
		{{1,0,1}, true},
		{{0}, false},
		{{1}, true},
		{{0,0,0,0}, false},
	};

	for(const auto& t : test_data)
	{
		EXPECT_EQ(get_value_or(t.inputs), t.expected);
	}
}

TEST(gate_cpp, nor)
{
	struct
	{
		std::vector<bool> inputs;
		bool expected;
	}
	test_data[]
	{
		{{1,1,1,1}, false},
		{{1,0,1}, false},
		{{0}, true},
		{{1}, false},
		{{0,0,0,0}, true},
	};

	for(const auto& t : test_data)
	{
		EXPECT_EQ(get_value_nor(t.inputs), t.expected);
	}
}

TEST(gate_cpp, xor)
{
	struct
	{
		std::vector<bool> inputs;
		bool expected;
	}
	test_data[]
	{
		{{1,1,1,1}, false},
		{{1,0,1}, false},
		{{1,0,1,1}, true},
		{{0}, false},
		{{1}, true},
		{{0,0,0,0}, false},
	};

	for(const auto& t : test_data)
	{
		EXPECT_EQ(get_value_xor(t.inputs), t.expected);
	}
}

TEST(gate_cpp, xnor)
{
	struct
	{
		std::vector<bool> inputs;
		bool expected;
	}
	test_data[]
	{
		{{1,1,1,1}, true},
		{{1,0,1}, true},
		{{1,0,1,1}, false},
		{{0}, true},
		{{1}, false},
		{{0,0,0,0}, true},
	};

	for(const auto& t : test_data)
	{
		EXPECT_EQ(get_value_xnor(t.inputs), t.expected);
	}
}

TEST(gate_cpp, neg)
{
	struct
	{
		std::vector<bool> inputs;
		bool expected;
	}
	test_data[]
	{
		{{0}, true},
		{{1}, false},
	};

	for(const auto& t : test_data)
	{
		EXPECT_EQ(get_value_neg(t.inputs), t.expected);
	}
}