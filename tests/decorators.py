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


def benchmark(runs: int = 1, verbose: bool = False):
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
                print(
                    f"---------- Test number {i} executed in {(end - start):.5f}s ----------"
                )

            if runs > 1:
                print("\n")
                print("Average execution time: ")
                print(f"{(overall_time / num_tests):.5f}s")

        return wrapper if execute else None

    return inner
