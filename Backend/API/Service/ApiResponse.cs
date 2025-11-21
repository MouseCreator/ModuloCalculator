namespace API.Service
{
    public class ApiResponse<T>
    {
        public bool Success { get; set; }
        public T? Data { get; set; }
        public string? Error { get; set; }

        public static ApiResponse<T> SuccessResponse(T data) => new ApiResponse<T> { Success = true, Data = data };
        public static ApiResponse<T> ErrorResponse(string error) => new ApiResponse<T> { Success = false, Error = error };
    }
}
