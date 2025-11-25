#backend & math
FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS base
WORKDIR /app
EXPOSE 8080
EXPOSE 8081

FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build
ARG BUILD_CONFIGURATION=Debug
WORKDIR /src

RUN apt-get update && \
    apt-get install -y g++ build-essential flex bison libfl-dev && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y dos2unix
RUN find . -type f -print0 | xargs -0 dos2unix

COPY ["Backend/API/API.csproj", "Backend/API/"]
RUN dotnet restore "Backend/API/API.csproj"
COPY . .
WORKDIR "/src/Backend/API"
RUN dos2unix prepare-cpp-binaries.sh
RUN dotnet build "API.csproj" -c $BUILD_CONFIGURATION -o /app/build

FROM build AS publish
ARG BUILD_CONFIGURATION=Debug
RUN dotnet publish "API.csproj" -c $BUILD_CONFIGURATION -o /app/publish /p:UseAppHost=false

# Copy the wrapper.so file to the publish directory
COPY --from=build /src/Backend/API/cpp-lib-binaries/wrapper.so /app/publish/

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "API.dll"]
