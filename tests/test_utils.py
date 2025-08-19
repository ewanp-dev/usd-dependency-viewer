
def test_execution_time(function):
    """
    Records the amount of time it takes to execute the input function
    """
    def wrapper(*args, **kwargs):
        import time

        start: float = time.perf_counter()
        function(*args, **kwargs)
        end: float = time.perf_counter()
        print(f"{(end - start):.5f}s")

    return wrapper

def test_multiple_executions(num_tests: int = 1, execute: bool = True):
    """
    times the test a number of given times and returns execution time as well as
    the average execution time

    :args:
        num_tests: the number of times the function will run
        execute: enable or disable the wrapper
    """

    def inner(function):
        def wrapper(*args, **kwargs):
            import time

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

if __name__ == "__main__":
    
    @test_multiple_executions(num_tests=5)
    def test() -> None:
        """Test function, not for main use"""
        for i in range(10):
            print(i)

    test()
