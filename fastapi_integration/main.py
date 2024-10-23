from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
import math, sys, os
# Add the build directory to sys.path so Python can find the compiled module
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'build')))
import integration  # This imports the C++ bindings

# Create FastAPI app
app = FastAPI()

# Define a request model
class IntegrationRequest(BaseModel):
    function_name: str  # The function to integrate ('x^3', 'sin(x)', etc.)
    a: float            # Lower limit of integration
    b: float            # Upper limit of integration
    n_threads: int      # Number of threads to use


# Function map to match string names to actual Python functions
function_map = {
    'x^3': lambda x: x ** 3,
    'sin(x)': math.sin
}


@app.post("/integrate")
async def integrate(request: IntegrationRequest):
    a = request.a
    b = request.b
    n_threads = request.n_threads
    func_name = request.function_name

    # Get the function from the map or raise an error
    if func_name not in function_map:
        raise HTTPException(status_code=400, detail="Unsupported function")

    function = function_map[func_name]

    # Call the C++ bindings based on the function
    if func_name == 'x^3':
        trapezoidal = integration.TrapezoidalIntegration()  # No custom function needed for x^3
    else:
        trapezoidal = integration.TrapezoidalIntegration(function)

    try:
        result = round(trapezoidal.compute(a, b, n_threads), 5)
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

    # Return a JSON response
    return {
        "function": func_name,
        "limits": {"a": a, "b": b},
        "result": result
    }
