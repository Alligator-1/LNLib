# LNLib C API - coverage report

This report maps every public symbol of the LNLib C++ kernel (as extracted from the headers by libclang and cross-checked with clang-query) to its binding in the C API.

- Public LNLib symbols: **371**
- Mapped to a C binding: **371**
- Uncovered: **0**

## (free)

| Symbol | Kind | C binding |
|---|---|---|
| `Contains` | function | `lnlib_octree_contains` |
| `Inside` | function | `lnlib_octree_inside` |
| `OctreeConstruction` | function | `lnlib_octree_create` |
| `OctreeKnnSearch` | function | `lnlib_octree_knn_search` |
| `OctreeRadiusSearch` | function | `lnlib_octree_radius_search` |
| `OctreeRadiusSearchFast` | function | `lnlib_octree_radius_search (FAST mode)` |
| `Overlaps` | function | `lnlib_octree_overlaps` |
| `bitrv` | function | `lnlib_fft_bitrv` |
| `bitrv2` | function | `lnlib_fft_bitrv2` |
| `cdft` | function | `lnlib_fft_cdft` |
| `ddct` | function | `lnlib_fft_ddct` |
| `ddst` | function | `lnlib_fft_ddst` |
| `dfct` | function | `lnlib_fft_dfct` |
| `dfst` | function | `lnlib_fft_dfst` |
| `operator*` | function | `value operators (add/subtract/scale/cross)` |
| `operator+` | function | `value operators` |
| `operator-` | function | `value operators` |
| `operator/` | function | `value operators` |
| `operator^` | function | `lnlib_uv_cross_product / lnlib_xyz_cross_product` |
| `rdft` | function | `lnlib_fft_rdft` |
| `scomp` | function | `lnlib_voronoi_scomp` |

## BezierCurve

| Symbol | Kind | C binding |
|---|---|---|
| `Check` | method | `lnlib_beziercurve_check` |
| `ComputerMiddleControlPointsOnQuadraticCurve` | method | `lnlib_beziercurve_compute_middle_control_points_on_quadratic` |
| `GetPointOnCurveByBernstein` | method | `lnlib_beziercurve_get_point_by_bernstein[_rational]` |
| `GetPointOnCurveByDeCasteljau` | method | `lnlib_beziercurve_get_point_by_de_casteljau[_rational]` |
| `GetPointOnQuadraticArc` | method | `lnlib_beziercurve_get_point_on_quadratic_arc` |

## BezierSurface

| Symbol | Kind | C binding |
|---|---|---|
| `Check` | method | `lnlib_beziersurface_check` |
| `GetPointOnSurfaceByDeCasteljau` | method | `lnlib_beziersurface_get_point_by_de_casteljau[_rational]` |

## BinaryIntegrationFunction

| Symbol | Kind | C binding |
|---|---|---|
| `operator()` | method | `lnlib_binary_integration_function callback (lnlib_integrator_simpson_2d)` |

## BsplineCurve

| Symbol | Kind | C binding |
|---|---|---|
| `Check` | method | `lnlib_bsplinecurve_check` |
| `ComputeControlPointsOfDerivatives` | method | `lnlib_bsplinecurve_compute_control_points_of_derivatives` |
| `ComputeDerivatives` | method | `lnlib_bsplinecurve_compute_derivatives` |
| `ComputeDerivativesByAllBasisFunctions` | method | `lnlib_bsplinecurve_compute_derivatives_by_all_basis_functions` |
| `GetPointOnCurve` | method | `lnlib_bsplinecurve_get_point[_rational]` |

## BsplineSurface

| Symbol | Kind | C binding |
|---|---|---|
| `Check` | method | `lnlib_bsplinesurface_check` |
| `ComputeControlPointsOfDerivatives` | method | `lnlib_bsplinesurface_compute_control_points_of_derivatives` |
| `ComputeDerivatives` | method | `lnlib_bsplinesurface_compute_derivatives` |
| `ComputeDerivativesByAllBasisFunctions` | method | `lnlib_bsplinesurface_compute_derivatives_by_all_basis_functions` |
| `ComputeFirstOrderDerivative` | method | `lnlib_bsplinesurface_compute_first_order_derivative` |
| `GetPointOnSurface` | method | `lnlib_bsplinesurface_get_point[_rational]` |

## ControlPointsUtils

| Symbol | Kind | C binding |
|---|---|---|
| `Multiply` | method | `lnlib_controlpoints_multiply_coefficient_by_points` |
| `ToXYZ` | method | `lnlib_controlpoints_to_xyz` |
| `ToXYZW` | method | `lnlib_controlpoints_to_xyzw_grid` |

## DistIndex

| Symbol | Kind | C binding |
|---|---|---|
| `DistIndex` | constructor | `lnlib_distindex_create` |
| `operator<` | method | `lnlib_distindex_less` |

## IntegrationFunction

| Symbol | Kind | C binding |
|---|---|---|
| `operator()` | method | `lnlib_integration_function callback (lnlib_integrator_*)` |

## Integrator

| Symbol | Kind | C binding |
|---|---|---|
| `ChebyshevSeries` | method | `lnlib_integrator_chebyshev_series` |
| `ClenshawCurtisQuadrature` | method | `lnlib_integrator_clenshaw_curtis_quadrature` |
| `ClenshawCurtisQuadrature2` | method | `lnlib_integrator_clenshaw_curtis_quadrature2` |
| `Simpson` | method | `lnlib_integrator_simpson` |

## Interpolation

| Symbol | Kind | C binding |
|---|---|---|
| `AverageKnotVector` | method | `lnlib_interpolation_average_knot_vector` |
| `ComputeKnotVector` | method | `lnlib_interpolation_compute_knot_vector` |
| `ComputeTangent` | method | `lnlib_interpolation_compute_tangent` |
| `ComputerWeightForRationalQuadraticInterpolation` | method | `lnlib_interpolation_compute_weight_for_rational_quadratic` |
| `GetCentripetalLength` | method | `lnlib_interpolation_get_centripetal_length` |
| `GetCentripetalParameterization` | method | `lnlib_interpolation_get_centripetal_parameterization` |
| `GetChordParameterization` | method | `lnlib_interpolation_get_chord_parameterization` |
| `GetSurfaceMeshParameterization` | method | `lnlib_interpolation_get_surface_mesh_parameterization` |
| `GetTotalChordLength` | method | `lnlib_interpolation_get_total_chord_length` |

## Intersection

| Symbol | Kind | C binding |
|---|---|---|
| `ComputeLineAndPlane` | method | `lnlib_intersection_compute_line_and_plane` |
| `ComputeRays` | method | `lnlib_intersection_compute_rays` |

## KnnResultSet

| Symbol | Kind | C binding |
|---|---|---|
| `AddPoint` | method | `lnlib_knn_result_set_add_point` |
| `Full` | method | `lnlib_knn_result_set_full` |
| `KnnResultSet` | constructor | `lnlib_knn_result_set_add_point` |
| `Results` | method | `lnlib_knn_result_set_get_results` |
| `Size` | method | `lnlib_knn_result_set_size` |
| `WorstDist` | method | `lnlib_knn_result_set_worst_dist` |

## KnotVectorUtils

| Symbol | Kind | C binding |
|---|---|---|
| `GetContinuity` | method | `lnlib_knotvector_get_continuity` |
| `GetInsertedKnotElement` | method | `lnlib_knotvector_get_inserted_knot_element` |
| `GetInsertedKnotElements` | method | `lnlib_knotvector_get_inserted_knot_elements` |
| `GetInternalKnotMultiplicityMap` | method | `lnlib_knotvector_get_internal_knot_multiplicity_map` |
| `GetKnotMultiplicityMap` | method | `lnlib_knotvector_get_knot_multiplicity_map` |
| `IsUniform` | method | `lnlib_knotvector_is_uniform` |
| `Rescale` | method | `lnlib_knotvector_rescale` |

## LN_BoundingBox3d

| Symbol | Kind | C binding |
|---|---|---|
| `Intersects` | method | `lnlib_bounding_box3d_intersects` |

## MathUtils

| Symbol | Kind | C binding |
|---|---|---|
| `AngleToRadians` | method | `lnlib_mathutils_angle_to_radians` |
| `Binomial` | method | `lnlib_mathutils_binomial` |
| `ComputeOBBAxes` | method | `lnlib_mathutils_compute_obb_axes` |
| `ComputerCubicEquationsWithOneVariable` | method | `lnlib_mathutils_computer_cubic_equations_with_one_variable` |
| `CreateMatrix` | method | `lnlib_mathutils_create_matrix` |
| `Factorial` | method | `lnlib_mathutils_factorial` |
| `GetColumn` | method | `lnlib_mathutils_get_column` |
| `GetDeterminant` | method | `lnlib_mathutils_get_determinant` |
| `IsAlmostEqualTo` | method | `lnlib_mathutils_is_almost_equal_to` |
| `IsGreaterThan` | method | `lnlib_mathutils_is_greater_than` |
| `IsGreaterThanOrEqual` | method | `lnlib_mathutils_is_greater_than_or_equal` |
| `IsInfinite` | method | `lnlib_mathutils_is_infinite` |
| `IsLessThan` | method | `lnlib_mathutils_is_less_than` |
| `IsLessThanOrEqual` | method | `lnlib_mathutils_is_less_than_or_equal` |
| `IsNaN` | method | `lnlib_mathutils_is_nan` |
| `MakeDiagonal` | method | `lnlib_mathutils_make_diagonal` |
| `MakeInverse` | method | `lnlib_mathutils_make_inverse` |
| `MatrixMultiply` | method | `lnlib_mathutils_matrix_multiply` |
| `RadiansToAngle` | method | `lnlib_mathutils_radians_to_angle` |
| `SolveLinearSystem` | method | `lnlib_mathutils_solve_linear_system` |
| `SolveLinearSystemBanded` | method | `lnlib_mathutils_solve_linear_system_banded` |
| `Transpose` | method | `lnlib_mathutils_transpose` |

## Matrix4d

| Symbol | Kind | C binding |
|---|---|---|
| `CreateReflection` | method | `lnlib_matrix4d_create_reflection` |
| `CreateRotation` | method | `lnlib_matrix4d_create_rotation` |
| `CreateRotationAtPoint` | method | `lnlib_matrix4d_create_rotation_at_point` |
| `CreateScale` | method | `lnlib_matrix4d_create_scale` |
| `CreateTranslation` | method | `lnlib_matrix4d_create_translation` |
| `GetBasisW` | method | `lnlib_matrix4d_get_basis_w` |
| `GetBasisX` | method | `lnlib_matrix4d_get_basis_x` |
| `GetBasisY` | method | `lnlib_matrix4d_get_basis_y` |
| `GetBasisZ` | method | `lnlib_matrix4d_get_basis_z` |
| `GetDeterminant` | method | `lnlib_matrix4d_get_determinant` |
| `GetElement` | method | `lnlib_matrix4d_get_element` |
| `GetInverse` | method | `lnlib_matrix4d_get_inverse` |
| `GetScale` | method | `lnlib_matrix4d_get_scale` |
| `GetTranspose` | method | `lnlib_matrix4d_get_transpose` |
| `HasReflection` | method | `lnlib_matrix4d_has_reflection` |
| `IsIdentity` | method | `lnlib_matrix4d_is_identity` |
| `IsTranslation` | method | `lnlib_matrix4d_is_translation` |
| `Matrix4d` | constructor | `lnlib_matrix4d_create` |
| `Multiply` | method | `lnlib_matrix4d_multiply` |
| `OfPoint` | method | `lnlib_matrix4d_of_point` |
| `OfVector` | method | `lnlib_matrix4d_of_vector` |
| `OfWeightedPoint` | method | `lnlib_matrix4d_of_weighted_point` |
| `SetBasisW` | method | `lnlib_matrix4d_set_basis_w` |
| `SetBasisX` | method | `lnlib_matrix4d_set_basis_x` |
| `SetBasisY` | method | `lnlib_matrix4d_set_basis_y` |
| `SetBasisZ` | method | `lnlib_matrix4d_set_basis_z` |
| `SetElement` | method | `lnlib_matrix4d_set_element` |
| `operator=` | method | `value semantics (copy)` |

## NurbsCurve

| Symbol | Kind | C binding |
|---|---|---|
| `ApproximateLength` | method | `lnlib_nurbs_curve_approximate_length` |
| `Bending` | method | `lnlib_nurbs_curve_bending` |
| `CanComputeDerivative` | method | `lnlib_nurbs_curve_can_compute_derivative` |
| `Check` | method | `lnlib_nurbs_curve_check` |
| `ComputeRationalCurveDerivatives` | method | `lnlib_nurbs_curve_compute_derivatives` |
| `ComputerRemoveKnotErrorBound` | method | `lnlib_nurbs_curve_compute_remove_knot_error_bound` |
| `ConstraintBasedModification` | method | `lnlib_nurbs_curve_constraint_based_modification` |
| `CreateArc` | method | `lnlib_nurbs_curve_create_arc` |
| `CreateCubicHermite` | method | `lnlib_nurbs_curve_create_cubic_hermite` |
| `CreateLine` | method | `lnlib_nurbs_curve_create_line` |
| `CreateOneConicArc` | method | `lnlib_nurbs_curve_create_one_conic_arc` |
| `CreateOpenConic` | method | `lnlib_nurbs_curve_create_open_conic` |
| `CreateTransformed` | method | `lnlib_nurbs_curve_create_transformed` |
| `CubicLocalInterpolation` | method | `lnlib_nurbs_curve_cubic_local_interpolation` |
| `Curvature` | method | `lnlib_nurbs_curve_curvature` |
| `DecomposeToBeziers` | method | `lnlib_nurbs_curve_decompose_to_beziers` |
| `ElevateDegree` | method | `lnlib_nurbs_curve_elevate_degree` |
| `EquallyTessellate` | method | `lnlib_nurbs_curve_equally_tessellate` |
| `Extend` | method | `lnlib_nurbs_curve_extend` |
| `Extract` | method | `lnlib_nurbs_curve_extract` |
| `FitWithConic` | method | `lnlib_nurbs_curve_fit_with_conic` |
| `FitWithCubic` | method | `lnlib_nurbs_curve_fit_with_cubic` |
| `Flattening` | method | `lnlib_nurbs_curve_flattening` |
| `GetAllParamsOnCurve` | method | `lnlib_nurbs_curve_get_all_params` |
| `GetParamOnCurve` | method | `lnlib_nurbs_curve_get_param / get_param_by_length` |
| `GetParamsOnCurve` | method | `lnlib_nurbs_curve_get_params_by_equal_length` |
| `GetPointOnCurve` | method | `lnlib_nurbs_curve_get_point` |
| `GetPointOnCurveByCornerCut` | method | `lnlib_nurbs_curve_get_point_by_corner_cut` |
| `GlobalApproximationByErrorBound` | method | `lnlib_nurbs_curve_global_approximation_by_error_bound` |
| `GlobalInterpolation` | method | `lnlib_nurbs_curve_global_interpolation` |
| `InsertKnot` | method | `lnlib_nurbs_curve_insert_knot` |
| `IsArc` | method | `lnlib_nurbs_curve_is_arc` |
| `IsClamp` | method | `lnlib_nurbs_curve_is_clamp` |
| `IsClosed` | method | `lnlib_nurbs_curve_is_closed` |
| `IsLinear` | method | `lnlib_nurbs_curve_is_linear` |
| `IsPeriodic` | method | `lnlib_nurbs_curve_is_periodic` |
| `LeastSquaresApproximation` | method | `lnlib_nurbs_curve_least_squares_approximation` |
| `Merge` | method | `lnlib_nurbs_curve_merge` |
| `MoveControlPoint` | method | `lnlib_nurbs_curve_move_control_point` |
| `NeighborWeightsModification` | method | `lnlib_nurbs_curve_neighbor_weights_modification` |
| `Normal` | method | `lnlib_nurbs_curve_normal` |
| `Offset` | method | `lnlib_nurbs_curve_offset` |
| `ProjectNormal` | method | `lnlib_nurbs_curve_project_normal` |
| `ReduceDegree` | method | `lnlib_nurbs_curve_reduce_degree` |
| `RefineKnotVector` | method | `lnlib_nurbs_curve_refine_knot_vector` |
| `RemoveExcessiveKnots` | method | `lnlib_nurbs_curve_remove_excessive_knots` |
| `RemoveKnot` | method | `lnlib_nurbs_curve_compute_remove_knot_error_bound` |
| `RemoveKnotsByGivenBound` | method | `lnlib_nurbs_curve_remove_knots_by_given_bound` |
| `Reparametrize` | method | `lnlib_nurbs_curve_reparametrize` |
| `Reverse` | method | `lnlib_nurbs_curve_reverse` |
| `SplitArc` | method | `lnlib_nurbs_curve_split_arc` |
| `SplitAt` | method | `lnlib_nurbs_curve_split_at` |
| `Tessellate` | method | `lnlib_nurbs_curve_equally_tessellate` |
| `ToClampCurve` | method | `lnlib_nurbs_curve_to_clamp` |
| `ToUnclampCurve` | method | `lnlib_nurbs_curve_to_unclamp` |
| `Torsion` | method | `lnlib_nurbs_curve_torsion` |
| `Warping` | method | `lnlib_nurbs_curve_warping` |
| `WeightModification` | method | `lnlib_nurbs_curve_weight_modification` |
| `WeightedAndContrainedLeastSquaresApproximation` | method | `lnlib_nurbs_curve_weighted_constrained_least_squares` |

## NurbsSurface

| Symbol | Kind | C binding |
|---|---|---|
| `ApproximateArea` | method | `lnlib_nurbs_surface_approximate_area` |
| `BicubicLocalInterpolation` | method | `lnlib_nurbs_surface_bicubic_local_interpolation` |
| `Check` | method | `lnlib_nurbs_surface_check` |
| `ComputeRationalSurfaceDerivatives` | method | `lnlib_nurbs_surface_compute_derivatives` |
| `ComputeRationalSurfaceFirstOrderDerivative` | method | `lnlib_nurbs_surface_compute_first_order_derivative` |
| `ComputeSignedDistanceFunction` | method | `lnlib_nurbs_surface_signed_distance` |
| `CreateBilinearSurface` | method | `lnlib_nurbs_surface_create_bilinear_surface` |
| `CreateCoonsSurface` | method | `lnlib_nurbs_surface_create_coons_surface` |
| `CreateCylindricalSurface` | method | `lnlib_nurbs_surface_create_cylindrical_surface` |
| `CreateGeneralizedTranslationalSweepSurface` | method | `lnlib_nurbs_surface_create_generalized_translational_sweep_surface` |
| `CreateGordonSurface` | method | `lnlib_nurbs_surface_create_gordon_surface` |
| `CreateLoftSurface` | method | `lnlib_nurbs_surface_create_loft_surface` |
| `CreateRevolvedSurface` | method | `lnlib_nurbs_surface_create_revolved_surface` |
| `CreateRuledSurface` | method | `lnlib_nurbs_surface_create_ruled_surface` |
| `CreateSweepSurface` | method | `lnlib_nurbs_surface_create_sweep_surface` |
| `CreateSwungSurface` | method | `lnlib_nurbs_surface_create_swung_surface` |
| `Curvature` | method | `lnlib_nurbs_surface_curvature` |
| `DecomposeToBeziers` | method | `lnlib_nurbs_surface_decompose_to_beziers` |
| `ElevateDegree` | method | `lnlib_nurbs_surface_elevate_degree` |
| `EquallyTessellate` | method | `lnlib_nurbs_surface_equally_tessellate` |
| `GetAllParamsOnSurface` | method | `lnlib_nurbs_surface_get_all_params` |
| `GetBoundingBox` | method | `lnlib_nurbs_surface_get_bounding_box` |
| `GetIsoCurve` | method | `lnlib_nurbs_surface_get_iso_curve` |
| `GetOrientedBoundingBox` | method | `lnlib_nurbs_surface_get_oriented_bounding_box` |
| `GetParamOnSurface` | method | `lnlib_nurbs_surface_get_param` |
| `GetParamOnSurfaceByGSA` | method | `lnlib_nurbs_surface_get_param_by_gsa` |
| `GetPointOnSurface` | method | `lnlib_nurbs_surface_get_point` |
| `GetUVTangent` | method | `lnlib_nurbs_surface_get_uv_tangent` |
| `GlobalApproximation` | method | `lnlib_nurbs_surface_global_approximation` |
| `GlobalInterpolation` | method | `lnlib_nurbs_surface_global_interpolation` |
| `InsertKnot` | method | `lnlib_nurbs_surface_insert_knot` |
| `IsClosed` | method | `lnlib_nurbs_surface_is_closed` |
| `MakeCornerFilletSurface` | method | `lnlib_nurbs_surface_make_corner_fillet_surface` |
| `NonUniformScaling` | method | `lnlib_nurbs_surface_non_uniform_scaling` |
| `Normal` | method | `lnlib_nurbs_surface_normal` |
| `ReduceDegree` | method | `lnlib_nurbs_surface_reduce_degree` |
| `RefineKnotVector` | method | `lnlib_nurbs_surface_refine_knot_vector` |
| `RemoveKnot` | method | `lnlib_nurbs_surface_remove_knot` |
| `Reparametrize` | method | `lnlib_nurbs_surface_reparametrize` |
| `Reverse` | method | `lnlib_nurbs_surface_reverse` |
| `Swap` | method | `lnlib_nurbs_surface_swap` |
| `Triangulate` | method | `lnlib_nurbs_surface_triangulate` |

## NurbsVolume

| Symbol | Kind | C binding |
|---|---|---|
| `Check` | method | `lnlib_nurbs_volume_check` |
| `ComputeVolumeRationalDerivatives` | method | `lnlib_nurbs_volume_compute_derivatives` |
| `ElevateDegree` | method | `lnlib_nurbs_volume_elevate_degree` |
| `Extract` | method | `lnlib_nurbs_volume_extract` |
| `GetIsoCurve` | method | `lnlib_nurbs_volume_get_iso_curve` |
| `GetParamOnVolume` | method | `lnlib_nurbs_volume_get_param` |
| `GetPointOnVolume` | method | `lnlib_nurbs_volume_get_point` |
| `InsertKnot` | method | `lnlib_nurbs_volume_insert_knot` |
| `IsClosed` | method | `lnlib_nurbs_volume_is_closed` |
| `RefineKnotVector` | method | `lnlib_nurbs_volume_refine_knot_vector` |
| `Reverse` | method | `lnlib_nurbs_volume_reverse` |
| `SplitAt` | method | `lnlib_nurbs_volume_split_at` |
| `Swap` | method | `lnlib_nurbs_volume_swap` |

## Octant

| Symbol | Kind | C binding |
|---|---|---|
| `Octant` | constructor | `created by lnlib_octree_create (no public C ctor)` |
| `~Octant` | destructor | `lnlib_octant_destroy (handle) / lnlib_octree_destroy (tree)` |

## Polynomials

| Symbol | Kind | C binding |
|---|---|---|
| `AllBasisFunctions` | method | `lnlib_polynomials_all_basis_functions` |
| `AllBernstein` | method | `lnlib_polynomials_all_bernstein` |
| `BasisFunctions` | method | `lnlib_polynomials_all_basis_functions` |
| `BasisFunctionsDerivatives` | method | `lnlib_polynomials_basis_functions_derivatives` |
| `BasisFunctionsFirstOrderDerivative` | method | `lnlib_polynomials_basis_functions_first_order_derivative` |
| `Bernstein` | method | `lnlib_polynomials_all_bernstein` |
| `BezierToPowerMatrix` | method | `lnlib_polynomials_bezier_to_power_matrix` |
| `GetKnotMultiplicity` | method | `lnlib_polynomials_get_knot_multiplicity` |
| `GetKnotSpanIndex` | method | `lnlib_polynomials_get_knot_span_index` |
| `Horner` | method | `lnlib_polynomials_horner` |
| `OneBasisFunction` | method | `lnlib_polynomials_one_basis_function` |
| `OneBasisFunctionDerivative` | method | `lnlib_polynomials_one_basis_function_derivative` |
| `PowerToBezierMatrix` | method | `lnlib_polynomials_power_to_bezier_matrix` |

## Projection

| Symbol | Kind | C binding |
|---|---|---|
| `PointToLine` | method | `lnlib_projection_point_to_line` |
| `PointToRay` | method | `lnlib_projection_point_to_ray` |
| `Stereographic` | method | `lnlib_projection_stereographic` |

## RadiusNnResultSet

| Symbol | Kind | C binding |
|---|---|---|
| `AddPoint` | method | `lnlib_radius_nn_result_set_add_point` |
| `RadiusNnResultSet` | constructor | `lnlib_radius_nn_result_set_add_point` |
| `Results` | method | `lnlib_radius_nn_result_set_get_results` |
| `Size` | method | `lnlib_radius_nn_result_set_size` |
| `WorstDist` | method | `lnlib_radius_nn_result_set_worst_dist` |

## UV

| Symbol | Kind | C binding |
|---|---|---|
| `Add` | method | `lnlib_uv_add` |
| `CrossProduct` | method | `lnlib_uv_cross_product` |
| `Distance` | method | `lnlib_uv_distance` |
| `DotProduct` | method | `lnlib_uv_dot_product` |
| `GetU` | method | `lnlib_uv_get_u` |
| `GetV` | method | `lnlib_uv_get_v` |
| `IsAlmostEqualTo` | method | `lnlib_uv_is_almost_equal_to` |
| `IsUnit` | method | `lnlib_uv_is_unit` |
| `IsZero` | method | `lnlib_uv_is_zero` |
| `Length` | method | `lnlib_uv_length` |
| `Negative` | method | `lnlib_uv_negative` |
| `Normalize` | method | `lnlib_uv_normalize` |
| `SetU` | method | `lnlib_uv_set_u` |
| `SetV` | method | `lnlib_uv_set_v` |
| `SqrLength` | method | `lnlib_uv_sqr_length` |
| `Substract` | method | `lnlib_uv_subtract` |
| `U` | method | `lnlib_uv_add` |
| `UV` | constructor | `lnlib_uv_add` |
| `V` | method | `lnlib_uv_add` |
| `operator*` | method | `lnlib_uv_scale via add/scale` |
| `operator*=` | method | `value semantics` |
| `operator+` | method | `lnlib_uv_add` |
| `operator+=` | method | `lnlib_uv_add (value semantics)` |
| `operator-` | method | `lnlib_uv_subtract` |
| `operator-=` | method | `lnlib_uv_subtract (value semantics)` |
| `operator/=` | method | `value semantics` |
| `operator=` | method | `value semantics (copy)` |
| `operator[]` | method | `lnlib_uv_get_component / lnlib_uv_set_component` |

## UVW

| Symbol | Kind | C binding |
|---|---|---|
| `GetU` | method | `lnlib_uvw_get_u` |
| `GetV` | method | `lnlib_uvw_get_v` |
| `GetW` | method | `lnlib_uvw_get_w` |
| `SetU` | method | `lnlib_uvw_set_u` |
| `SetV` | method | `lnlib_uvw_set_v` |
| `SetW` | method | `lnlib_uvw_set_w` |
| `U` | method | `lnlib_uvw_create` |
| `UVW` | constructor | `lnlib_uvw_create` |
| `V` | method | `lnlib_uvw_create` |
| `W` | method | `lnlib_uvw_create` |

## ValidationUtils

| Symbol | Kind | C binding |
|---|---|---|
| `ComputeCurveModifyTolerance` | method | `lnlib_validation_compute_curve_modify_tolerance` |
| `IsValidBezier` | method | `lnlib_validation_is_valid_bezier` |
| `IsValidBspline` | method | `lnlib_validation_is_valid_bspline` |
| `IsValidDegreeReduction` | method | `lnlib_validation_is_valid_degree_reduction` |
| `IsValidKnotVector` | method | `lnlib_validation_is_valid_knot_vector` |
| `IsValidNurbs` | method | `lnlib_validation_is_valid_nurbs` |

## VoronoiDiagramGenerator

| Symbol | Kind | C binding |
|---|---|---|
| `VoronoiDiagramGenerator` | constructor | `lnlib_voronoi_create` |
| `generateVoronoi` | method | `lnlib_voronoi_set_generate_voronoi` |
| `getNext` | method | `lnlib_voronoi_get_edges` |
| `getNextDelaunay` | method | `lnlib_voronoi_get_delaunay_edges` |
| `getNextVertex` | method | `lnlib_voronoi_get_vertices` |
| `getNextVertexPair` | method | `lnlib_voronoi_get_vertex_pairs` |
| `getTriangles` | method | `lnlib_voronoi_get_triangles` |
| `reset` | method | `lnlib_voronoi_reset_delaunay_edges_iterator` |
| `resetDelaunayEdgesIterator` | method | `lnlib_voronoi_reset_delaunay_edges_iterator` |
| `resetIterator` | method | `lnlib_voronoi_reset_edge_iterator` |
| `resetVertexPairIterator` | method | `lnlib_voronoi_reset_vertex_pair_iterator` |
| `resetVerticesIterator` | method | `lnlib_voronoi_reset_vertices_iterator` |
| `setGenerateDelaunay` | method | `lnlib_voronoi_set_generate_delaunay` |
| `setGenerateVoronoi` | method | `lnlib_voronoi_set_generate_voronoi` |
| `~VoronoiDiagramGenerator` | destructor | `lnlib_voronoi_destroy` |

## XYZ

| Symbol | Kind | C binding |
|---|---|---|
| `Add` | method | `lnlib_xyz_add` |
| `AngleTo` | method | `lnlib_xyz_angle_to` |
| `CreateRandomOrthogonal` | method | `lnlib_xyz_create_random_orthogonal` |
| `CrossProduct` | method | `lnlib_xyz_cross_product` |
| `Distance` | method | `lnlib_xyz_distance` |
| `DotProduct` | method | `lnlib_xyz_dot_product` |
| `GetX` | method | `lnlib_xyz_get_x` |
| `GetY` | method | `lnlib_xyz_get_y` |
| `GetZ` | method | `lnlib_xyz_get_z` |
| `IsAlmostEqualTo` | method | `lnlib_xyz_is_almost_equal_to` |
| `IsUnit` | method | `lnlib_xyz_is_unit` |
| `IsZero` | method | `lnlib_xyz_is_zero` |
| `Length` | method | `lnlib_xyz_length` |
| `Negative` | method | `lnlib_xyz_negative` |
| `Normalize` | method | `lnlib_xyz_normalize` |
| `SetX` | method | `lnlib_xyz_set_x` |
| `SetY` | method | `lnlib_xyz_set_y` |
| `SetZ` | method | `lnlib_xyz_set_z` |
| `SqrLength` | method | `lnlib_xyz_sqr_length` |
| `Substract` | method | `lnlib_xyz_subtract` |
| `X` | method | `lnlib_xyz_add` |
| `XYZ` | constructor | `lnlib_xyz_add` |
| `Y` | method | `lnlib_xyz_add` |
| `Z` | method | `lnlib_xyz_add` |
| `operator*` | method | `lnlib_xyz_scale` |
| `operator*=` | method | `lnlib_xyz_scale (value semantics)` |
| `operator+` | method | `lnlib_xyz_add` |
| `operator+=` | method | `lnlib_xyz_add (value semantics)` |
| `operator-` | method | `lnlib_xyz_subtract` |
| `operator-=` | method | `lnlib_xyz_subtract (value semantics)` |
| `operator/=` | method | `lnlib_xyz_scale (value semantics)` |
| `operator=` | method | `value semantics (copy)` |
| `operator[]` | method | `lnlib_xyz_get_component / lnlib_xyz_set_component` |

## XYZW

| Symbol | Kind | C binding |
|---|---|---|
| `Distance` | method | `lnlib_xyzw_distance` |
| `GetW` | method | `lnlib_xyzw_get_w` |
| `GetWX` | method | `lnlib_xyzw_get_wx` |
| `GetWY` | method | `lnlib_xyzw_get_wy` |
| `GetWZ` | method | `lnlib_xyzw_get_wz` |
| `IsAlmostEqualTo` | method | `lnlib_xyzw_is_almost_equal_to` |
| `SetW` | method | `lnlib_xyzw_set_w` |
| `ToXYZ` | method | `lnlib_xyzw_to_xyz` |
| `W` | method | `lnlib_xyzw_add` |
| `WX` | method | `lnlib_xyzw_get_wx` |
| `WY` | method | `lnlib_xyzw_get_wy` |
| `WZ` | method | `lnlib_xyzw_get_wz` |
| `XYZW` | constructor | `lnlib_xyzw_add` |
| `operator+` | method | `lnlib_xyzw_add` |
| `operator+=` | method | `lnlib_xyzw_add (value semantics)` |
| `operator-` | method | `lnlib_xyzw_subtract` |
| `operator[]` | method | `lnlib_xyzw_get_component / lnlib_xyzw_set_component` |
