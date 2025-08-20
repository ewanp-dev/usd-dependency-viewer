"""
TODOs

rework this entire file, make it more streamlined towards usd

- @expect_exception
- @benchmark (replace multiple executions)
- @retry
- @skip
- look at parameters
- @timeout
- @validate output
- @snapshot

"""


def proof_execution_time(function):
    """
    Records the amount of time it takes to execute the input function
    """

    def wrapper(*args, **kwargs):
        # TODO: Test exceptions for imports
        import time

        start: float = time.perf_counter()
        function(*args, **kwargs)
        end: float = time.perf_counter()
        print(f"{(end - start):.5f}s")

    return wrapper


def proof_multiple_executions(num_tests: int = 1, execute: bool = True):
    """
    executes the function a given number of times, returning information in the process

    :args:
        num_tests: the number of times the function will run

    :execute:
        enables or disables the decorator
    """

    def inner(function):
        def wrapper(*args, **kwargs):
            import time

            # TODO: add more information, add in a verbose mode

            overall_time: float = 0
            for i in range(num_tests):
                i += 1
                start: float = time.perf_counter()
                function(*args, **kwargs)
                end: float = time.perf_counter()
                overall_time += end - start
                print(f"Test number: {i} | Execution time: {(end - start):.5f}s")

            print("\n")
            print("Average execution time: ")
            print(f"{(overall_time / num_tests):.5f}s")

        return wrapper if execute else None

    return inner
