namespace API.Service.Middlewares
{
    public class ResponseMiddleware
    {
        private readonly RequestDelegate _next;

        public ResponseMiddleware(RequestDelegate next) => _next = next;

        public async Task InvokeAsync(HttpContext context)
        {
            context.Response.ContentType = "application/json";

            try
            {
                await _next(context);
            }
            catch (Exception ex)
            {
                var errorResponse = ApiResponse<string>.ErrorResponse(ex.Message);
                context.Response.StatusCode = StatusCodes.Status500InternalServerError;
                await context.Response.WriteAsJsonAsync(errorResponse);
            }
        }
    }
}