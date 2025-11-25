
# front
FROM node:20-alpine AS frontend-final

# Set the working directory inside the container
WORKDIR /app

# Copy package.json and package-lock.json from the "front" folder
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy the rest of the application code from the "front" folder
COPY . .
# Build the application
ENV PORT=3000
EXPOSE 3000

CMD ["npm", "run", "dev"]