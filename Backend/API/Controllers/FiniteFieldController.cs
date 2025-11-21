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
        
    }
    
    public class FiniteFieldOperationRequest
    {
        public string expr { get; set; }
        public string? n { get; set; }
    }
    
    
}