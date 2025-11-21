namespace API.Service.Middlewares
{
    public class TimeoutMiddleware
    {
        private readonly RequestDelegate _next;
        private readonly TimeSpan _timeout = TimeSpan.FromSeconds(10);

        public TimeoutMiddleware(RequestDelegate next) => _next = next;

        public async Task InvokeAsync(HttpContext context)
        {
            using (var cts = new CancellationTokenSource(_timeout))
            {
                var timeoutTask = Task.Delay(_timeout, cts.Token);

                var requestTask = _next(context);

                // wait for request proccessed, or timeout
                var completedTask = await Task.WhenAny(requestTask, timeoutTask);

                if (completedTask == timeoutTask)
                {
                    // timeout
                    context.Response.StatusCode = StatusCodes.Status408RequestTimeout;
                    var timeoutResponse = ApiResponse<string>.ErrorResponse("Час на виконання операції вичерпано");
                    await context.Response.WriteAsJsonAsync(timeoutResponse);
                }
                else
                {
                    // continue executing if time limit not exeeded
                    cts.Cancel();
                    await requestTask; // end request proccessing
                }
            }
        }
    }

}
