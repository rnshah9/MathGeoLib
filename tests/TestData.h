#include "../src/MathBuildConfig.h"
#include "../src/MathGeoLibFwd.h"
#include "../src/Math/assume.h"

MATH_BEGIN_NAMESPACE

namespace TestData
{

float *PosFloatArray();
Quat *QuatArray();
float *FloatArray();
float4x4 *MatrixArray();
float4x4 *MatrixArray2();
float4x4 *TransposedMatrixArray();
float2 *Float2Array();
float4 *VectorArray();
float4 *VectorArray2();

// N.B. These must be static and not extern to not generate UDB with initialization order between compilation units!
static DONT_WARN_UNUSED float *f = FloatArray();
static DONT_WARN_UNUSED float *pf = PosFloatArray();
static DONT_WARN_UNUSED float4x4 *m = MatrixArray();
static DONT_WARN_UNUSED float4x4 *m2 = MatrixArray2();
static DONT_WARN_UNUSED float4x4 *tpm = TransposedMatrixArray();
static DONT_WARN_UNUSED float2 *fl_2 = Float2Array();
static DONT_WARN_UNUSED float4 *v = VectorArray();
static DONT_WARN_UNUSED float4 *v2 = VectorArray2();
static DONT_WARN_UNUSED Quat *q = QuatArray();

} // ~TestData

MATH_END_NAMESPACE