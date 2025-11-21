using System.Runtime.InteropServices;

namespace API.BinaryWrappers
{
	public class CppDllMethods
	{
		public static class FiniteFieldMethods
		{
			[DllImport("wrapper.so")]
			public static extern unsafe byte* finite_field(byte* expression, byte* n, byte* errorStr);

			[DllImport("wrapper.so")]
			public static extern unsafe byte* random_prime(byte* errorStr);
			
			[DllImport("wrapper.so")]
			public static extern unsafe byte* number_factorization(byte* n, byte* errorStr);
			
			[DllImport("wrapper.so")]
			public static extern unsafe byte* number_order(byte* number, byte* n, byte* errorStr);
			
			[DllImport("wrapper.so")]
			public static extern unsafe byte* random_number(byte* errorStr);
			
			[DllImport("wrapper.so")]
			public static extern unsafe byte* prime_test(byte* number, byte* iterations, byte* errorStr);




		}

	}
}