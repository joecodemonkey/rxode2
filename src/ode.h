#define __HD_ODE_1__ "#include <stdio.h>\n#include <stdarg.h>\n#include <R.h>\n#include <Rinternals.h>\n#include <Rmath.h>\n#include <R_ext/Rdynload.h>\n#define JAC_Rprintf Rprintf\n#define _idx (&_solveData->subjects[_cSub])->idx\n#define JAC0_Rprintf if ( (&_solveData->subjects[_cSub])->jac_counter == 0) Rprintf\n#define ODE_Rprintf Rprintf\n#define ODE0_Rprintf if ( (&_solveData->subjects[_cSub])->dadt_counter == 0) Rprintf\n#define LHS_Rprintf Rprintf\n#define _safe_log(a) (((a) <= 0) ? log(DOUBLE_EPS) : log(a))\n#define safe_zero(a) ((a) == 0 ? DOUBLE_EPS : (a))\n#define _as_zero(a) (fabs(a) < sqrt(DOUBLE_EPS) ? 0.0 : a)\n#define factorial(a) exp(lgamma1p(a))\n#define sign_exp(sgn, x)(((sgn) > 0.0) ? exp(x) : (((sgn) < 0.0) ? -exp(x) : 0.0))\n#define R_pow(a, b) (((a) == 0 && (b) <= 0) ? R_pow(DOUBLE_EPS, b) : R_pow(a, b))\n#define R_pow_di(a, b) (((a) == 0 && (b) <= 0) ? R_pow_di(DOUBLE_EPS, b) : R_pow_di(a, b))\n#define Rx_pow(a, b) (((a) == 0 && (b) <= 0) ? R_pow(DOUBLE_EPS, b) : R_pow(a, b))\n#define Rx_pow_di(a, b) (((a) == 0 && (b) <= 0) ? R_pow_di(DOUBLE_EPS, b) : R_pow_di(a, b))\ntypedef void (*t_dydt)(int *neq, double t, double *A, double *DADT);\ntypedef void (*t_calc_jac)(int *neq, double t, double *A, double *JAC, unsigned int __NROWPD__);\ntypedef void (*t_calc_lhs)(int cSub, double t, double *A, double *lhs);\ntypedef void (*t_update_inis)(int cSub, double *);\ntypedef void (*t_dydt_lsoda_dum)(int *neq, double *t, double *A, double *DADT);\ntypedef void (*t_jdum_lsoda)(int *neq, double *t, double *A,int *ml, int *mu, double *JAC, int *nrowpd);\ntypedef int (*t_dydt_liblsoda)(double t, double *y, double *ydot, void *data);\ntypedef void (*t_ode_current)();\n\ntypedef struct {\n  // These options should not change based on an individual solve\n  int badSolve;\n  double ATOL;          //absolute error\n  double RTOL;          //relative error\n  double H0;\n  double HMIN;\n  int mxstep;\n  int MXORDN;\n  int MXORDS;\n  //\n  int do_transit_abs;\n  int nlhs;\n  int neq;\n  int stiff;\n  int ncov;\n  char modNamePtr[1000];\n  int *par_cov;\n  double *inits;\n  double *scale;\n  int do_par_cov;\n  // approx fun options\n  double f1;\n  double f2;\n  int kind;\n  int is_locf;\n  int cores;\n  int extraCmt;\n  double hmax2; // Determined by diff\n  double *rtol2;\n  double *atol2;\n  int nDisplayProgress;\n  int ncoresRV;\n  int isChol;\n  int *svar;\n  int abort;\n} rx_solving_options;\n\n\ntypedef struct {\n  int *slvr_counter;\n  int *dadt_counter;\n  int *jac_counter;\n  double *InfusionRate;\n  int *BadDose;\n  int nBadDose;\n  double HMAX; // Determined by diff\n  double tlast;\n  double podo;\n  double *par_ptr;\n  double *dose;\n  double *solve;\n  double *lhs;\n  int  *evid;\n  int *rc;\n  double *cov_ptr;\n  int n_all_times;\n  int ixds;\n  int ndoses;\n  double *all_times;\n  double *dv;\n  int *idose;\n  int idosen;\n  int id;\n  int sim;\n  int idx;\n  double ylow;\n  double yhigh;\n  double lambda;\n  double yj;\n} rx_solving_options_ind;\n\ntypedef struct {\n  rx_solving_options_ind *subjects;\n  rx_solving_options *op;\n  int nsub;\n  int nsim;\n  int nall;\n  int nobs;\n  int nr;\n  int add_cov;\n  int matrix;\n  double stateTrim;\n  int *stateIgnore;\n} rx_solve;\n\ntypedef void (*t_set_solve)(rx_solve *);\ntypedef rx_solve *(*t_get_solve)();\n\n\nrx_solve *getRxSolve_();\nrx_solve *getRxSolve(SEXP ptr);\n\nvoid par_solve(rx_solve *rx);\n\nrx_solving_options *getRxOp(rx_solve *rx);\n\nSEXP RxODE_df(int doDose, int doTBS);\nSEXP RxODE_par_df();\n\nrx_solving_options_ind *rxOptionsIniEnsure(int mx);\n\nvoid rxUpdateFuns(SEXP trans);\n#define abs_log1p(x) (((x) + 1.0 > 0.0) ? log1p(x) : (((x) + 1.0 > 0.0) ? log1p(-x) : 0.0))\n#define abs_log(x) ((fabs(x) <= sqrt(DOUBLE_EPS)) ? log(sqrt(DOUBLE_EPS)) : (((x) > 0.0) ? log(x) ? (((x) == 0) ? 0.0 : log(-x))))\n#define _IR (_solveData->subjects[_cSub].InfusionRate)\n#define _PP (_solveData->subjects[_cSub].par_ptr)\n#define _SR (INTEGER(stateRmS))\n#define rx_lambda_ _solveData->subjects[_cSub].lambda\n#define rx_yj_ _solveData->subjects[_cSub].yj\n#define rxTBS(x, lm, y"
#define __HD_ODE_2__ "j)  _powerD(x,  lm, (int)(yj))\n#define rxTBSi(x, lm, yj) _powerDi(x,  lm, (int)(yj))\n#define rxTBSd(x, lm, yj) _powerDD(x, lm, (int)(yj))\n#define rxTBSd2(x, lm, yj) _powerDDD(x, lm, (int)(yj))\n\n// Types for par pointers.r\ntypedef double (*RxODE_fn) (double x);\ntypedef double (*RxODE_fn2) (double x, double y);\ntypedef double (*RxODE_fn3i) (double x, double y, int i);\ntypedef double (*RxODE_fn2i) (double x, int i);\ntypedef int (*RxODE_fn0i) ();\ntypedef double (*RxODE_vec) (int val, rx_solve *rx, unsigned int id);\ntypedef double (*RxODE_val) (rx_solve *rx, unsigned int id);\ntypedef void (*RxODE_assign_ptr)(SEXP);\ntypedef void (*RxODE_ode_solver_old_c)(int *neq,double *theta,double *time,int *evid,int *ntime,double *inits,double *dose,double *ret,double *atol,double *rtol,int *stiff,int *transit_abs,int *nlhs,double *lhs,int *rc);\n\nRxODE_fn3i _powerD, _powerDD, _powerDDD, _powerDi;\n\nRxODE_assign_ptr _assign_ptr = NULL;\n\ntypedef void (*_rxRmModelLibType)(const char *inp);\n_rxRmModelLibType _rxRmModelLib = NULL;\n\ntypedef SEXP (*_rxGetModelLibType)(const char *s);\n_rxGetModelLibType _rxGetModelLib = NULL;\n\nRxODE_ode_solver_old_c _old_c = NULL;\n\nRxODE_fn0i _ptrid=NULL;\n\ntypedef  SEXP (*_rx_asgn) (SEXP objectSEXP);\n_rx_asgn _RxODE_rxAssignPtr =NULL;\n\ntypedef int(*_rxIsCurrentC_type)(SEXP);\n_rxIsCurrentC_type _rxIsCurrentC=NULL;\n\ntypedef double(*_rxSumType)(double *, int, double *, int, int);\n_rxSumType _sumPS = NULL;\n\ndouble _sum(double *input, double *pld, int m, int type, int n, ...){\n  va_list valist;\n  va_start(valist, n);\n  for (unsigned int i = 0; i < n; i++){\n    input[i] = va_arg(valist, double);\n  }\n  va_end(valist);\n  return _sumPS(input, n, pld, m, type);\n}\n\ntypedef double(*_rxProdType)(double*, double*, int, int);\n_rxProdType _prodPS = NULL;\n\ndouble _prod(double *input, double *p, int type, int n, ...){\n  va_list valist;\n  va_start(valist, n);\n  for (unsigned int i = 0; i < n; i++){\n    input[i] = va_arg(valist, double);\n  }\n  va_end(valist);\n  return _prodPS(input, p, n, type);\n}\n\ndouble _sign(unsigned int n, ...){\n  va_list valist;\n  va_start(valist, n);\n  double s = 1;\n  for (unsigned int i = 0; i < n; i++){\n    s = sign(va_arg(valist, double))*s;\n    if (s == 0){\n      break;\n    }\n  }\n  va_end(valist);\n  return s;\n}\n\ndouble _max(unsigned int n, ...){\n  va_list valist;\n  va_start(valist, n);\n  double mx = NA_REAL;\n  double tmp = 0;\n  if (n >= 1){\n    mx = va_arg(valist, double);\n    for (unsigned int i = 1; i < n; i++){\n      tmp = va_arg(valist, double);\n      if (tmp>mx) mx=tmp;\n    }\n    va_end(valist);\n  }\n  return mx;\n}\n\ndouble _min(unsigned int n, ...){\n  va_list valist;\n  va_start(valist, n);\n  double mn = NA_REAL;\n  double tmp = 0;\n  if (n >= 1){\n    mn = va_arg(valist, double);\n    for (unsigned int i = 1; i < n; i++){\n      tmp = va_arg(valist, double);\n      if (tmp<mn) mn=tmp;\n    }\n    va_end(valist);\n  }\n  return mn;\n}\n\nrx_solve *_solveData = NULL;\n\ndouble _transit4P(double t, unsigned int id, double n, double mtt, double bio){\n  double ktr = (n+1)/mtt;\n  double lktr = log(n+1)-log(mtt);\n  double tc = (t-(_solveData->subjects[id].tlast));\n  return exp(log(bio*(_solveData->subjects[id].podo))+lktr+n*(lktr+log(tc))-ktr*(tc)-lgamma1p(n));\n}\n\ndouble _transit3P(double t, unsigned int id, double n, double mtt){\n  double ktr = (n+1)/mtt;\n  double lktr = log(n+1)-log(mtt);\n  double tc = (t-(_solveData->subjects[id].tlast));\n  return exp(log(_solveData->subjects[id].podo)+lktr+n*(lktr+log(tc))-ktr*(tc)-lgamma1p(n));\n}\n\ntypedef double (*solveLinB_p) (rx_solve *rx, unsigned int id, double t, int linCmt, int diff1, int diff2, double d_A, double d_alpha, double d_B, double d_beta, double d_C, double d_gamma, double d_ka, double d_tlag);\n\nsolveLinB_p solveLinB;\n\ntypedef void (*_update_par_ptr_p)(double t, unsigned int id, rx_solve *rx, int idx);\n\n_update_par_ptr_p _update_par_ptr;\n\nRxODE_fn0i _prodType = NULL;\nRxODE_fn0i _sumType = NULL;\n\nextern void __ODE_SOLVER_SOLVEDATA__ (rx_"
#define __HD_ODE_3__ "solve *solve){\n  _solveData = solve;\n}\n\nextern rx_solve *__ODE_SOLVER_GET_SOLVEDATA__(){\n  return _solveData;\n}\n\nSEXP __MODEL_VARS__();\nextern void __ODE_SOLVER__(int *neq,\n			   double *theta,      //order:\n			   double *time,\n			   int *evid,\n			   int *ntime,\n			   double *inits,\n			   double *dose,\n			   double *ret,\n			   double *atol,\n			   double *rtol,\n			   int *stiff,\n			   int *transit_abs,\n			   int *nlhs,\n			   double *lhs,\n			   int *rc){\n  // Backward compatible ode solver for 0.5* C interface\n  //if (_ptrid() != __TIMEID__ ){ _assign_ptr(__MODEL_VARS__());}\n  __FIX_INIS__\n  _old_c(neq, _theta, time, evid, ntime, inits, dose, ret, atol, rtol, stiff, transit_abs, nlhs, lhs, rc);\n}\n\nstatic R_NativePrimitiveArgType __ODE_SOLVER__rx_t[] = {\n  //*neq, *theta, *time,  *evid, *ntime, *inits,   *dose,   *ret,     *atol,  *rtol,   *stiff, *transit_abs, *nlhs, *lhs, *rc\n  INTSXP,REALSXP, REALSXP, INTSXP, INTSXP, REALSXP, REALSXP, REALSXP, REALSXP, REALSXP, INTSXP, INTSXP, INTSXP, REALSXP, INTSXP\n};\n"
#define __HD_ODE_4__ ""
#define __HD_SOLVE1__ "\nextern void __DYDT_LSODA__(int *neq, double *t, double *A, double *DADT)\n{\n  __DYDT__(neq, *t, A, DADT);\n}\n\nextern int __DYDT_LIBLSODA__(double t, double *y, double *ydot, void *data)\n{\n  int *neq = (int*)(data);\n  __DYDT__(neq, t, y, ydot);\n  return(0);\n}\n\nextern void __CALC_JAC_LSODA__(int *neq, double *t, double *A,int *ml, int *mu, double *JAC, int *nrowpd){\n  // Update all covariate parameters\n  __CALC_JAC__(neq, *t, A, JAC, *nrowpd);\n}\n\n//Initilize the dll to match RxODE's calls\nvoid __R_INIT__ (DllInfo *info){\n  // Get C callables on load; Otherwise it isn't thread safe\n  _assign_ptr=(RxODE_assign_ptr) R_GetCCallable(\"RxODE\",\"RxODE_assign_fn_pointers\");\n  _rxRmModelLib=(_rxRmModelLibType) R_GetCCallable(\"RxODE\",\"rxRmModelLib\");\n  _rxGetModelLib=(_rxGetModelLibType) R_GetCCallable(\"RxODE\",\"rxGetModelLib\");\n  _old_c = (RxODE_ode_solver_old_c) R_GetCCallable(\"RxODE\",\"rxSolveOldC\");\n  _RxODE_rxAssignPtr=(_rx_asgn)R_GetCCallable(\"RxODE\",\"_RxODE_rxAssignPtr\");\n  _rxIsCurrentC = (_rxIsCurrentC_type)R_GetCCallable(\"RxODE\",\"rxIsCurrentC\");\n  _sumPS  = (_rxSumType) R_GetCCallable(\"PreciseSums\",\"PreciseSums_sum_r\");\n  _prodPS = (_rxProdType) R_GetCCallable(\"PreciseSums\",\"PreciseSums_prod_r\");\n  _prodType=(RxODE_fn0i)R_GetCCallable(\"PreciseSums\", \"PreciseSums_prod_get\");\n  _sumType=(RxODE_fn0i)R_GetCCallable(\"PreciseSums\", \"PreciseSums_sum_get\");\n  _ptrid=(RxODE_fn0i)R_GetCCallable(\"RxODE\", \"RxODE_current_fn_pointer_id\");\n  _powerD=(RxODE_fn3i)R_GetCCallable(\"RxODE\", \"powerD\");\n  _powerDi=(RxODE_fn3i)R_GetCCallable(\"RxODE\", \"powerDi\");\n  _powerDD=(RxODE_fn3i)R_GetCCallable(\"RxODE\", \"powerDD\");\n  _powerDDD=(RxODE_fn3i)R_GetCCallable(\"RxODE\", \"powerDDD\");\n  solveLinB=(solveLinB_p)R_GetCCallable(\"RxODE\", \"solveLinB\");\n  _update_par_ptr=(_update_par_ptr_p) R_GetCCallable(\"RxODE\",\"_update_par_ptr\");\n  // Register the outside functions\n  R_RegisterCCallable(__LIB_STR__,__ODE_SOLVER_STR__,       (DL_FUNC) __ODE_SOLVER__);\n  R_RegisterCCallable(__LIB_STR__,\"__INIS__\", (DL_FUNC) __INIS__);\n  R_RegisterCCallable(__LIB_STR__,\"__INIS__\", (DL_FUNC) __INIS__);\n  R_RegisterCCallable(__LIB_STR__,\"__DYDT__\", (DL_FUNC) __DYDT__);\n  R_RegisterCCallable(__LIB_STR__,\"__CALC_LHS__\", (DL_FUNC) __CALC_LHS__);\n  R_RegisterCCallable(__LIB_STR__,\"__CALC_JAC__\", (DL_FUNC) __CALC_JAC__);\n  R_RegisterCCallable(__LIB_STR__,\"__DYDT_LSODA__\", (DL_FUNC) __DYDT_LSODA__);\n  R_RegisterCCallable(__LIB_STR__,\"__CALC_JAC_LSODA__\", (DL_FUNC) __CALC_JAC_LSODA__);\n  R_RegisterCCallable(__LIB_STR__,\"__ODE_SOLVER_SOLVEDATA__\", (DL_FUNC) __ODE_SOLVER_SOLVEDATA__);\n  R_RegisterCCallable(__LIB_STR__,\"__ODE_SOLVER_GET_SOLVEDATA__\", (DL_FUNC) __ODE_SOLVER_GET_SOLVEDATA__);\n  R_RegisterCCallable(__LIB_STR__,\"__DYDT_LIBLSODA__\", (DL_FUNC) __DYDT_LIBLSODA__);\n  \n  static const R_CMethodDef cMethods[] = {\n    {__ODE_SOLVER_STR__, (DL_FUNC) &__ODE_SOLVER__, 15, __ODE_SOLVER__rx_t},\n    {NULL, NULL, 0, NULL}\n  };\n  \n  R_CallMethodDef callMethods[]  = {\n    {__MODEL_VARS_STR__, (DL_FUNC) &__MODEL_VARS__, 0},\n    {NULL, NULL, 0}\n  };\n  R_registerRoutines(info, cMethods, callMethods, NULL, NULL);\n  R_useDynamicSymbols(info,FALSE);\n}\n\nvoid __R_UNLOAD__ (DllInfo *info){\n  // Free resources required for single subject solve.\n  SEXP _mv = PROTECT(_rxGetModelLib(__MODEL_VARS_STR__));\n  if (!isNull(_mv)){\n    _rxRmModelLib(__MODEL_VARS_STR__);\n  }\n  UNPROTECT(1);\n}"
#define __HD_SOLVE2__ ""
#define __VER_2__ "    SET_STRING_ELT(version,2,mkChar(\"468b2fd3681be7452327b6618edd78c5\"));\n"
#define __VER_1__ "    SET_STRING_ELT(version,1,mkChar(\"https://github.com/nlmixrdevelopment/RxODE\"));\n"
#define __VER_0__ "    SET_STRING_ELT(version,0,mkChar(\"0.8.0-5\"));\n"
#define __VER_md5__ "468b2fd3681be7452327b6618edd78c5"
