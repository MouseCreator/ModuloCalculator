using API.Endpoints;
using API.Service.Middlewares;

var builder = WebApplication.CreateBuilder(new WebApplicationOptions
{
    Args = args,
    ApplicationName = typeof(Program).Assembly.FullName,
    ContentRootPath = Directory.GetCurrentDirectory(),
    EnvironmentName = Environments.Development
});

builder.WebHost.UseUrls("http://0.0.0.0:8080");

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
builder.Services.AddControllers();

builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowAnyOriginPolicy",
        policy => policy.AllowAnyOrigin()
                        .AllowAnyHeader()
                        .AllowAnyMethod());
});

var app = builder.Build();

app.UseCors("AllowAnyOriginPolicy");

app.UseSwagger();
app.UseSwaggerUI();

//app.UseHttpsRedirection();

app.UseMiddleware<TimeoutMiddleware>();
app.UseMiddleware<ResponseMiddleware>();

app.MapGeneral_Get();
app.MapControllers();

app.Run();