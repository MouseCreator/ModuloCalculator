# Finite Field Calculator (Long Modular Arithmetic System)

This project is a small web app for working with long modular arithmetic and basic number theory.

- **Backend:** ASP.NET Core + native C++ library (`wrapper.so`)
- **Frontend:** React, TanStack Router, Redux
- **Protocol:** JSON REST API over HTTP (`/S` prefix)

---

## 1. User Guide

### 1.1. What the app does

The app lets you:

- evaluate expressions in a finite field;
- factor numbers;
- compute the multiplicative order of a number modulo *n*;
- run a probabilistic primality test;
- generate random primes / numbers.

Everything is done through a simple web UI.

---

### 1.2. Main layout

The UI is split into:

- **Left sidebar**
    - Search bar (visual for now).
    - Navigation tree:
        - **Main page** – overview of the system.
        - **Finite field operations** – all math tools.
- **Top bar**
    - Left: **info button** (`i`) that opens an external user guide in a new tab (if configured).
    - Center: current operation name.
- **Center area**
    - On main page – description + main buttons.
    - On tools – input fields, operation buttons, and *Calculate* button.
- **Right / bottom area**
    - Latest **output**.
    - **Log list** of previous results.

---

### 1.3. Main page

The app starts on the **main** page.

There you usually see:

- a short text describing the system;
- button to open the **calculator**;
- button to open a **full user guide** in the browser.

No calculations happen on this page.

---

### 1.4. Finite field calculator

This is the main calculator for expressions in a finite field.

You have:

- **Expression input** – type something like `2+3*5`, `sqrt(5)`, `log(3)`, etc.
- **Operation buttons** – for quick insert:
    - `sqrt()`, `log()`, `eul()`, `kar()`, `+`, `-`, `*`, `/`, `^`, `(`, `)`.
    - Clicking a button inserts its text into the expression at the cursor.
- **Field size input** – labeled “Field size” (the modulus `n`).
- **RPN button** – asks backend for a random prime and puts it into the field size input.
- **Calculate button** – sends expression and field size to the backend.

Result appears in the **Output** field and is also added to the **Log list**.

---

### 1.5. Number factorization

There is a separate route for **number factorization**.

Usage is simple:

1. Select *Number factorization* in the left menu.
2. Enter an integer in the expression input (e.g. `840`).
3. Click **Calculate**.
4. You get a factorization string (e.g. `2^3 * 3 * 5 * 7`) in Output + it is stored in Log.

The second input (field size) is not used here.

---

### 1.6. Number order

There is a route for **multiplicative order** of a number modulo `n`.

1. Select *Number order* in the menu.
2. In the expression field, type the base number.
3. In the second input, type the modulus `n` (often a prime; there may be a default like `41`).
4. Press **Calculate**.

You get a string like `ord_41(2) = 5` in the Output.

---

### 1.7. Probabilistic primality test

There is a route for **prime test**.

1. Select *Probabilistic prime test*.
2. Expression field: number to test.
3. Second input: number of iterations (labelled “Iterations”).
4. Press **Calculate**.

You get a short text result (e.g. “probably prime” / “composite”, exact wording depends on the C++ code).  
The result is added to the log.

---

### 1.8. Log / history

For all routes except the main page you also see a **Log list**:

- read-only textarea with all previous results, one per line;
- button **Clear** to wipe the history.

This is stored in Redux state for the current session in the browser.

---

## 2. Getting Started

### 2.1. Prerequisites

You will need:

- **.NET SDK** (version that matches the project; .NET 6+ is enough for typical setup);
- **Node.js + npm** (or yarn/pnpm) for the frontend;
- C++ toolchain to build the native library as **`wrapper.so`**.

---

### 2.2. Backend setup

1. **Build C++ library**

   Build your C++ code into a shared library:

   ```bash
   # Example for Linux
   g++ -shared -fPIC -o wrapper.so your_cpp_sources.cpp ...
   ```

   Place `wrapper.so` where the backend can find it (e.g. in the output folder next to the DLL, or in a directory from `LD_LIBRARY_PATH`).

2. **Run backend**

   From the backend project folder:

   ```bash
   dotnet restore
   dotnet run
   ```

   By default it listens on:

    - `http://0.0.0.0:8080`

   All APIs are under the `/S` prefix (for example `http://localhost:8080/S/finite_field`).

CORS is configured to allow any origin, so the frontend can call it in development.

---

### 2.3. Frontend setup

1. Go to your frontend folder:

   ```bash
   cd frontend   # adjust if your path is different
   npm install
   ```

2. The frontend uses an Axios instance with:

   ```js
   baseURL: 'http://localhost:8080/S/'
   ```

   If your backend runs on another host/port, change this in `instance.js`.

3. Start dev server:

   ```bash
   npm run dev
   ```

   Open the shown URL in the browser (e.g. `http://localhost:5173/` if you use Vite).

Make sure backend and frontend run at the same time.

---

### 2.4. Notes

- For production you probably want HTTPS and stricter CORS on the backend.
- Frontend can be built with `npm run build` and served by any static file server.

---

## 3. API Documentation

All routes below are:

- base URL: `http://localhost:8080`
- prefix: `/S`

So, for example, the full path for finite field is: `POST http://localhost:8080/S/finite_field`.

### 3.1. Response format

Most endpoints return:

```json
{
  "success": true,
  "data": ...,
  "error": null
}
```

or, if something went wrong:

```json
{
  "success": false,
  "data": null,
  "error": "Some message"
}
```

Some very simple validation errors may use plain `BadRequest` responses from ASP.NET, but the normal path uses this `ApiResponse<T>` wrapper.

---

### 3.2. General / test endpoints

#### `POST /S/test`

Simple health-check.

- **Request body:** empty
- **Response:**

  ```json
  {
    "success": true,
    "data": "Тестовий запит пройшов успішно",
    "error": null
  }
  ```

---

#### `POST /S/error`

Always returns an error, useful to test error handling.

- **Request body:** empty
- **Response:**

  ```json
  {
    "success": false,
    "data": null,
    "error": "Щось пішло не так"
  }
  ```

---

#### `GET /S/testTimeout?delaySeconds={int}`

Used to test the timeout middleware.

- **Query:**
    - `delaySeconds` – delay in seconds.

If the request runs longer than 10 seconds, the middleware returns `408 Request Timeout` with an error message.

---

### 3.3. Math endpoints

#### `POST /S/finite_field`

Evaluate expression in a finite field.

- **Body:**

  ```json
  {
    "expr": "2+3*5",
    "n": 41
  }
  ```

    - `expr` – expression as a string.
    - `n` – field size (modulus), usually a prime.

- **Response (success):**

  ```json
  {
    "success": true,
    "data": {
      "result": "17"
    },
    "error": null
  }
  ```

---

#### `POST /S/random_prime`

Generate a random prime (used mainly to fill the “Field size” input).

- **Body:** `{}` (no fields required; request type may support `min`/`max` but backend can ignore them)
- **Response (success):**

  ```json
  {
    "success": true,
    "data": {
      "result": "99991"
    },
    "error": null
  }
  ```

---

#### `POST /S/number_factorization`

Factor an integer.

- **Body:**

  ```json
  {
    "n": "840"
  }
  ```

- **Response (success):**

  ```json
  {
    "success": true,
    "data": {
      "result": "2^3 * 3 * 5 * 7"
    },
    "error": null
  }
  ```

---

#### `POST /S/number_order`

Compute multiplicative order of a number modulo `n`.

- **Body:**

  ```json
  {
    "number": "2",
    "n": "41"
  }
  ```

- **Response (success):**

  ```json
  {
    "success": true,
    "data": "ord_41(2) = 5",
    "error": null
  }
  ```

Note: here `data` is a plain string.

---

#### `POST /S/random_number`

Generate a random number.

- **Body:** `{}` (request type allows `min`/`max`, but they may be ignored)
- **Response (success):**

  ```json
  {
    "success": true,
    "data": {
      "result": "123456"
    },
    "error": null
  }
  ```

---

#### `POST /S/prime_test`

Probabilistic primality test.

- **Body:**

  ```json
  {
    "number": "99991",
    "iterations": 20
  }
  ```

- **Response (success):**

  ```json
  {
    "success": true,
    "data": "99991 is probably prime",
    "error": null
  }
  ```

Exact wording for `data` comes from the C++ library.

---
"Sincerely, students of INF-1"
