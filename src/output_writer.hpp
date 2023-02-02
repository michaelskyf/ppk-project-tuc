#pragma once

#include "parser_input.hpp"

/**
 * @brief Write the processed data to a stream
 *
 * @param[in]	stream		Stream where the data will be saved
 *
 * @param[in]	input		Vector containing lines with input states
 *
 * @param[in]	output		Vector containing lines with output states
 *
 * @return
 *			- true on success
 *			- false on failure
 */
bool output_write(std::ostream& stream, const std::vector<InputLine>& input, const std::vector<OutputLine>& output);