using Microsoft.AspNetCore.Mvc;
using API.BinaryWrappers;
using API.Service;

namespace API.Controllers 
{
    [ApiController]
    [Route("S")]
    public class FiniteFieldController : ControllerBase
    {
        [HttpPost("finite_field")]
        public ActionResult<Dictionary<string, string>> Add([FromBody] FiniteFieldOperationRequest request)
        {
            if (request == null)
            {
                return BadRequest("Request cannot be null.");
            }

            string errorStr = string.Empty;
            var result = FiniteFieldWrapper.ExecuteFiniteField(request.expr, request.n, ref errorStr);
            var resultDict = new Dictionary<string, string>
            {
                { "result", result}
            };

            if (!string.IsNullOrEmpty(errorStr))
            {
                return BadRequest(ApiResponse<string>.ErrorResponse(errorStr));
            }

            return Ok(ApiResponse<Dictionary<string, string>>.SuccessResponse(resultDict));
        }

        [HttpPost("random_prime")]
        public ActionResult<Dictionary<string, string>> Random([FromBody] RandomPrimeRequest request)
        {
            if (request == null)
            {
                return BadRequest("Request cannot be null.");
            }

            string errorStr = string.Empty;
            var result = FiniteFieldWrapper.generate_random_prime(ref errorStr);
            var resultDict = new Dictionary<string, string>
            {
                { "result", result}
            };

            if (!string.IsNullOrEmpty(errorStr))
            {
                return BadRequest(ApiResponse<string>.ErrorResponse(errorStr));
            }

            return Ok(ApiResponse<Dictionary<string, string>>.SuccessResponse(resultDict));
        }

        [HttpPost("number_factorization")]
        public ActionResult<Dictionary<string, string>> Factorize([FromBody] NumberFactorizationRequest request)
        {
            if (request == null)
            {
                return BadRequest("Request cannot be null.");
            }

            string errorStr = string.Empty;
            var result = FiniteFieldWrapper.number_factorization(request.n, ref errorStr);
            var resultDict = new Dictionary<string, string>
            {
                { "result", result}
            };

            if (!string.IsNullOrEmpty(errorStr))
            {
                return BadRequest(ApiResponse<string>.ErrorResponse(errorStr));
            }

            return Ok(ApiResponse<Dictionary<string, string>>.SuccessResponse(resultDict));
        }

        [HttpPost("number_order")]
        public ActionResult<string> Order([FromBody] NumberOrderRequest request)
        {
            if (request == null)
            {
                return BadRequest("Request cannot be null.");
            }

            string errorStr = string.Empty;
            var result = FiniteFieldWrapper.number_order(request.number, request.n, ref errorStr);

            if (!string.IsNullOrEmpty(errorStr))
            {
                return BadRequest(ApiResponse<string>.ErrorResponse(errorStr));
            }

            return Ok(ApiResponse<string>.SuccessResponse(result));
        }
        
        [HttpPost("random_number")]
        public ActionResult<Dictionary<string, string>> Random([FromBody] RandomNumberRequest request)
        {
            if (request == null)
            {
                return BadRequest("Request cannot be null.");
            }

            string errorStr = string.Empty;
            var result = FiniteFieldWrapper.random_number(ref errorStr);
            var resultDict = new Dictionary<string, string>
            {
                { "result", result}
            };

            if (!string.IsNullOrEmpty(errorStr))
            {
                return BadRequest(ApiResponse<string>.ErrorResponse(errorStr));
            }

            return Ok(ApiResponse<Dictionary<string, string>>.SuccessResponse(resultDict));
        }
        
    }

    public class FiniteFieldOperationRequest
    {
        public string expr { get; set; }
        public string? n { get; set; }
    }
    
    public class RandomPrimeRequest
    {
        public string? min { get; set; }
        public string? max { get; set; }
    }

    public class NumberFactorizationRequest
    {
        public string? n { get; set; }
    }

    public class NumberOrderRequest
    {
        public string? number { get; set; }
        public string? n { get; set; }
    }
    
    public class RandomNumberRequest
    {
        public string? min { get; set; }
        public string? max { get; set; }
    }
}