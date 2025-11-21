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

}
