# Pull Request Template

## 📝 Description
Provide a brief overview of the changes introduced in this pull request. Include the context and purpose of the changes, summarizing what the PR accomplishes and why it is necessary.

## ✅ Type of Change
Indicate the type of change this PR introduces by checking the appropriate box(es):

- [ ] Bug Fix (corrects an issue)
- [ ] New Feature (adds new functionality)
- [ ] Performance Improvement (enhances efficiency or speed)
- [ ] Refactoring (code restructuring without changing behavior)
- [ ] Documentation Update (changes to documentation)
- [ ] Other (please specify): ________

## ❗ Problem Statement
Clearly describe the specific problem or issue this PR addresses. Include relevant background information, such as bug reports, feature requests, or performance issues.

- **Issue Reference**: Provide a link to the Rational Team Concert (RTC) issue number (e.g., `Link to RTC #123`) or describe if no issue exists.
- **Impact**: Explain how this problem affects the project or its users.

## 🔄 Steps to Reproduce
For bugs or issues, provide detailed steps to reproduce the problem. If this is a new feature, describe how to verify the functionality.

1. [Step 1]
2. [Step 2]
3. [Expected Behavior]
4. [Actual Behavior]

## 🛠️ Technical Approach
Explain the technical solution implemented in this PR. Include details about the design, algorithms, or C++-specific techniques used.

- **Changes Made**:
  - List key code changes (e.g., new classes, modified functions).
  - Highlight any C++/Cuda-specific considerations (e.g., use of smart pointers, STL, or multithreading).
- **Why This Approach**:
  - Justify the chosen solution over alternatives.
  - Mention trade-offs, if any (e.g., performance vs. readability).

## 📚 Lessons Learned
Document any insights or challenges encountered during development. This could include:
- **Uninitialized Variables**: Identified and resolved issues with uninitialized variables causing undefined behavior (e.g., random values in local variables). Adopted practices like initializing variables at declaration or using tools like Valgrind to detect uninitialized memory access.
- **Buffer Overflow**: Addressed buffer overflow vulnerabilities (e.g., writing beyond array bounds). Implemented bounds checking, used `std::vector` or `std::array` for safer memory management, and tested with tools like Valgrind/AddressSanitizer/COmpute-sanitizer to catch overflows.
- Defensive programming to handle impossible cases.
- Performance optimizations or debugging techniques.
- Best practices adopted (e.g., RAII, const-correctness).

## 🧪 Test Report: How Has This Been Tested

- **Unit Tests**:
  - List new or modified unit tests using Doctest for C++ code and pytest for Python code.
  - Example: `test_my_feature.cpp` , `test_rtcm_op.py` added to covering key functionality.
- **Edge Test Cases**:
  - List specific edge cases tested, such as boundary conditions or extreme inputs.
  - Example: Tested array with max size, empty input, or null pointers.
  - Confirm behavior for edge cases (e.g., handling `INT_MAX`, zero, or negative values).
- **Error Test Cases**:
  - List tests for invalid or malformed inputs to ensure robust error handling.
  - Example: Tested function with `nullptr`, invalid file paths, or out-of-range values
  - Describe how errors are handled (e.g., exceptions, error codes) and verify expected behavior.
- **Baseline Testing**:
  - List baseline tests performed using `testjob.py` and `analyzejob.py`.
  - generate summary reports.
  - Confirm no baseline shifting.
- **Integration Tests**:
  - Simulator testing
  - Tool testing
- **Performance Test Cases**:
  - List performance tests conducted to validate optimizations or ensure no regressions.
  - Describe the methodology (e.g., tools used, environment, input sizes).

- **Manual Testing**:
  - Steps performed manually to verify the fix or feature.
  
- **Test Results**:
  - Confirm all tests pass
  - Include any relevant metrics (e.g., performance benchmarks, memory usage).
  

## 📋 Checklist
- [ ] Code compiles without new warnings.
- [ ] All Doctest, pytest, baseline (testjob.py, analyzejob.py), and Viva tests pass locally and on CI.
- [ ] Code follows project style guidelines (e.g., naming conventions, formatting).
- [ ] Documentation updated (if applicable).
- [ ] Memory leaks checked (e.g., using Valgrind or AddressSanitizer).
- [ ] Performance considerations addressed (e.g., no regressions in benchmarks).

## ℹ️ Additional Notes
Add any other relevant information, such as:
- Dependencies introduced 
- Future improvements or known limitations.
- Screenshots or logs ( baseline test reports from analyzejob.py).
- List test environment and test data

---

## 👀 Reviewer Instructions
- Please verify the problem is resolved by following the "Steps to Reproduce."
- Check code for C++ best practices (e.g., memory safety, exception handling) and Python best practices (if applicable).
- Ensure cover edge cases, invalid inputs, and performance adequately.
- Review the testing strategy, baseline test results, and performance test results for accuracy and relevance.
  
