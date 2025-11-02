using System.Runtime.InteropServices;
using System.Text;

namespace API.BinaryWrappers;


public class FiniteFieldWrapper
{
    public static unsafe string  ExecuteFiniteField(string expr, string? number, ref string errStr)
    {
        try
        {
            // Convert input strings to ASCII byte arrays
            byte[] exprBytes = Encoding.ASCII.GetBytes(expr);
            byte[] nBytes = Encoding.ASCII.GetBytes(number ?? "");
            byte[] errorStrBytes = new byte[1024]; // Allocate a buffer for the error string

            fixed (byte* expression = exprBytes)
            fixed (byte* n = nBytes)
            fixed (byte* errStrPtr = errorStrBytes)
            {
                // Call the native C++ function
                byte* resultPtr = CppDllMethods.FiniteFieldMethods.finite_field(expression, n, errStrPtr);

                if (resultPtr == null)
                    throw new Exception("Result pointer is null, indicating a failure in native code.");

                // Calculate the result string length
                int resultLength = 0;
                while (resultPtr[resultLength] != 0)
                    resultLength++;

                // Copy the result to a managed byte array
                byte[] resultBytes = new byte[resultLength];
                Marshal.Copy((IntPtr)resultPtr, resultBytes, 0, resultLength);

                // Decode the result and error strings
                string resultStr = Encoding.ASCII.GetString(resultBytes);
                errStr = Encoding.ASCII.GetString(errorStrBytes).TrimEnd('\0');

                // Return both strings
                return resultStr;
            }
        }
        catch (Exception ex)
        {
            // Wrap exceptions with context information
            throw new Exception($"An error occurred while processing the finite field operation: {ex.Message}");
        }
    }
    
    
    public static unsafe string GenerateRandomNumber(string min, string max, ref string errStr)
    {
        try
        {
            // Convert input strings to ASCII byte arrays
            byte[] minBytes = Encoding.ASCII.GetBytes(min);
            byte[] maxBytes = Encoding.ASCII.GetBytes(max);
            byte[] errorStrBytes = new byte[1024]; // Allocate a buffer for the error string

            fixed (byte* minPtr = minBytes)
            fixed (byte* maxPtr = maxBytes)
            fixed (byte* errStrPtr = errorStrBytes)
            {
                // Call the native C++ function
                byte* resultPtr = CppDllMethods.FiniteFieldMethods.random_prime(minPtr, maxPtr, errStrPtr);

                if (resultPtr == null)
                    throw new Exception("Result pointer is null, indicating a failure in native code.");

                // Calculate the result string length
                int resultLength = 0;
                while (resultPtr[resultLength] != 0)
                    resultLength++;

                // Copy the result to a managed byte array
                byte[] resultBytes = new byte[resultLength];
                Marshal.Copy((IntPtr)resultPtr, resultBytes, 0, resultLength);

                // Decode the result and error strings
                string resultStr = Encoding.ASCII.GetString(resultBytes);
                errStr = Encoding.ASCII.GetString(errorStrBytes).TrimEnd('\0');

                // Return both strings
                return resultStr;
            }
        }
        catch (Exception ex)
        {
            // Wrap exceptions with context information
            throw new Exception($"An error occurred while processing the finite field operation: {ex.Message}");
        }
    }
    
    
    public static unsafe string number_factorization(string n, ref string errStr)
    {
        try
        {
            // Convert input strings to ASCII byte arrays
            byte[] nBytes = Encoding.ASCII.GetBytes(n);
            byte[] errorStrBytes = new byte[1024]; // Allocate a buffer for the error string

            fixed (byte* nPtr = nBytes)
            fixed (byte* errStrPtr = errorStrBytes)
            {
                // Call the native C++ function
                byte* resultPtr = CppDllMethods.FiniteFieldMethods.number_factorization(nPtr, errStrPtr);

                if (resultPtr == null)
                    throw new Exception("Result pointer is null, indicating a failure in native code.");

                // Calculate the result string length
                int resultLength = 0;
                while (resultPtr[resultLength] != 0)
                    resultLength++;

                // Copy the result to a managed byte array
                byte[] resultBytes = new byte[resultLength];
                Marshal.Copy((IntPtr)resultPtr, resultBytes, 0, resultLength);

                // Decode the result and error strings
                string resultStr = Encoding.ASCII.GetString(resultBytes);
                errStr = Encoding.ASCII.GetString(errorStrBytes).TrimEnd('\0');

                // Return both strings
                return resultStr;
            }
        }
        catch (Exception ex)
        {
            // Wrap exceptions with context information
            throw new Exception($"An error occurred while processing the finite field operation: {ex.Message}");
        }
    }
    
    
    public static unsafe string number_order(string number, string n, ref string errStr)
    {
        try
        {
            // Convert input strings to ASCII byte arrays
            byte[] numberBytes = Encoding.ASCII.GetBytes(number);
            byte[] nBytes = Encoding.ASCII.GetBytes(n);
            byte[] errorStrBytes = new byte[1024]; // Allocate a buffer for the error string

            fixed (byte* numberPtr = numberBytes)
            fixed (byte* nPtr = nBytes)
            fixed (byte* errStrPtr = errorStrBytes)
            {
                // Call the native C++ function
                byte* resultPtr = CppDllMethods.FiniteFieldMethods.number_order(numberPtr, nPtr, errStrPtr);

                if (resultPtr == null)
                    throw new Exception("Result pointer is null, indicating a failure in native code.");

                // Calculate the result string length
                int resultLength = 0;
                while (resultPtr[resultLength] != 0)
                    resultLength++;

                // Copy the result to a managed byte array
                byte[] resultBytes = new byte[resultLength];
                Marshal.Copy((IntPtr)resultPtr, resultBytes, 0, resultLength);

                // Decode the result and error strings
                string resultStr = Encoding.ASCII.GetString(resultBytes);
                errStr = Encoding.ASCII.GetString(errorStrBytes).TrimEnd('\0');

                // Return both strings
                return resultStr;
            }
        }
        catch (Exception ex)
        {
            // Wrap exceptions with context information
            throw new Exception($"An error occurred while processing the finite field operation: {ex.Message}");
        }
    }
    
    
    public static unsafe string random_number(string min, string max, ref string errStr)
    {
        try
        {
            // Convert input strings to ASCII byte arrays
            byte[] minBytes = Encoding.ASCII.GetBytes(min);
            byte[] maxBytes = Encoding.ASCII.GetBytes(max);
            byte[] errorStrBytes = new byte[1024]; // Allocate a buffer for the error string

            fixed (byte* minPtr = minBytes)
            fixed (byte* maxPtr = maxBytes)
            fixed (byte* errStrPtr = errorStrBytes)
            {
                // Call the native C++ function
                byte* resultPtr = CppDllMethods.FiniteFieldMethods.random_number(minPtr, maxPtr, errStrPtr);

                if (resultPtr == null)
                    throw new Exception("Result pointer is null, indicating a failure in native code.");

                // Calculate the result string length
                int resultLength = 0;
                while (resultPtr[resultLength] != 0)
                    resultLength++;

                // Copy the result to a managed byte array
                byte[] resultBytes = new byte[resultLength];
                Marshal.Copy((IntPtr)resultPtr, resultBytes, 0, resultLength);

                // Decode the result and error strings
                string resultStr = Encoding.ASCII.GetString(resultBytes);
                errStr = Encoding.ASCII.GetString(errorStrBytes).TrimEnd('\0');

                // Return both strings
                return resultStr;
            }
        }
        catch (Exception ex)
        {
            // Wrap exceptions with context information
            throw new Exception($"An error occurred while processing the finite field operation: {ex.Message}");
        }
    }
    
    public static unsafe string prime_test(string number, string iterations, ref string errStr)
    {
        try
        {
            // Convert input strings to ASCII byte arrays
            byte[] numberBytes = Encoding.ASCII.GetBytes(number);
            byte[] iterationsBytes = Encoding.ASCII.GetBytes(iterations);
            byte[] errorStrBytes = new byte[1024]; // Allocate a buffer for the error string

            fixed (byte* numberPtr = numberBytes)
            fixed (byte* iterationsPtr = iterationsBytes)
            fixed (byte* errStrPtr = errorStrBytes)
            {
                // Call the native C++ function
                byte* resultPtr = CppDllMethods.FiniteFieldMethods.prime_test(numberPtr, iterationsPtr, errStrPtr);

                if (resultPtr == null)
                    throw new Exception("Result pointer is null, indicating a failure in native code.");

                // Calculate the result string length
                int resultLength = 0;
                while (resultPtr[resultLength] != 0)
                    resultLength++;

                // Copy the result to a managed byte array
                byte[] resultBytes = new byte[resultLength];
                Marshal.Copy((IntPtr)resultPtr, resultBytes, 0, resultLength);

                // Decode the result and error strings
                string resultStr = Encoding.ASCII.GetString(resultBytes);
                errStr = Encoding.ASCII.GetString(errorStrBytes).TrimEnd('\0');

                // Return both strings
                return resultStr;
            }
        }
        catch (Exception ex)
        {
            // Wrap exceptions with context information
            throw new Exception($"An error occurred while processing the finite field operation: {ex.Message}");
        }
    }

}
