add_executable(
	${PROJECT_NAME}
	main.cpp
	gate.cpp
	simulator.cpp
	parser_input.cpp
	parser_circuit.cpp
	output_writer.cpp
	)

target_link_libraries(
	${PROJECT_NAME}
	)
