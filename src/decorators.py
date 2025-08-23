"""
Types of decorators
    benchmarks
    retries
    timeouts
    output validation
    snapshots
    random seeds
"""


def benchmark(num_tests: int = 1, skip: bool = False, constraint: float = 0):
    """
    times the test a number of given times and returns execution time
    as well as the average execution time

    :args:
        num_tests: the number of times the function will run
        skip: choose whether to run the benchmark or not
    """

    # TODO write a better time execution breakdown (fastest run, slowest run)
    # TODO write an expecation argument to see if it meets a certain time constraint

    def inner(function):
        def wrapper(*args, **kwargs):
            if not skip:
                import time

                fastest_run = {}
                overall_time: float = 0
                for _ in range(num_tests):
                    _ += 1
                    start: float = time.perf_counter()
                    function(*args, **kwargs)
                    overall_time += time.perf_counter() - start
                    print("\n#-------------------------------------------------#\n")
                    print(
                        f"Test number {_}... Execution time {(time.perf_counter() - start):.5f}s"
                    )
                    print("\n#-------------------------------------------------#\n")

                average_execution_time: float = overall_time / num_tests
                if constraint > 0:
                    if average_execution_time > constraint:
                        print(
                            f"WARNING: execution is over constraint time by {(average_execution_time - constraint):.5f}s"
                        )

                print("\n")
                print(f"Average execution time {average_execution_time:.5f}s")

        return wrapper

    return inner
