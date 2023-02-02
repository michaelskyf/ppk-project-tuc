#include <gtest/gtest.h>
#include <vector>
#include "../src/simulator.cpp"

TEST(simulator_cpp, simulation)
{
	// Circuit presented in the specification file
	const std::vector<ParsedGate> test_circuit =
	{
		{0, GateType::INPUT, {1,6}},
		{1, GateType::OUTPUT, {3}},
		{2, GateType::NAND, {1,6,5}},
		{3, GateType::NAND, {1,5,2}},
		{4, GateType::NAND, {5,6,4}},
		{5, GateType::NAND, {2,4,3}},
	};

	std::vector<InputLine> test_input =
	{
		{{1, 0}, {6, 0}},
		{{1, 0}, {6, 1}},
		{{1, 1}, {6, 0}},
		{{1, 1}, {6, 1}},
	};

	std::vector<OutputLine> expected_output =
	{
		{{3, 0}},
		{{3, 1}},
		{{3, 1}},
		{{3, 0}},
	};
	std::vector<OutputLine> output;

	auto prepared = prepare_simulation(test_circuit);
	auto& nodes = prepared.first;
	const auto& output_ids = prepared.second;
	EXPECT_FALSE(nodes.empty());

	for(const auto& input : test_input)
	{
		auto output_line = simulate_circuit(nodes, input, output_ids);
		if(!output_line.empty())
		{
			output.emplace_back(std::move(output_line));
		}
	}

	EXPECT_EQ(output.size(), expected_output.size());
	if(output.size() != expected_output.size())
	{
		FAIL();
	}

	for(size_t i = 0; i < output.size(); i++)
	{
		const auto& expected = expected_output[i];
		const auto& returned = output[i];

		EXPECT_EQ(returned[0].nodeID, expected[0].nodeID);
		EXPECT_EQ(returned[0].value, expected[0].value);
	}
}