.PHONY: clean All

All:
	@echo ----------Building project:[ TestCase - Debug ]----------
	@"make" -f "TestCase.mk" type=Debug 
clean:
	@echo ----------Building project:[ TestCase - Debug ]----------
	@"make" -f "TestCase.mk" type=Debug  clean
