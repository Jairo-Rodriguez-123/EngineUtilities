
#include <iostream>

#include "EngineUtilites.h"

int main() {
  std::cout.precision(4); 
  std::cout << std::fixed; 

  std::cout << "--- Prueba de mathEngine" << std::endl;

  
  std::cout << "\n--- Pruebas de EngineUtilities" << std::endl;
  float test_val = 25.0f;
  std::cout << "Muestra sqrt(" << test_val << "): " << EngineUtilities::Math::sqrt(test_val) << " (esperado 5.0000)" << std::endl;
  std::cout << "Muestra sqrt(2.0f): " << EngineUtilities::Math::sqrt(2.0f) << " (esperado 1.4142)" << std::endl;

  std::cout << "Muestra abs(-5.5f): " << EngineUtilities::Math::abs(-5.5f) << std::endl;
  std::cout << "Muestra EMax(10.0f, 20.0f): " << EngineUtilities::Math::EMax(10.0f, 20.0f) << std::endl;
  std::cout << "Muestra EMin(10.0f, 20.0f): " << EngineUtilities::Math::EMin(10.0f, 20.0f) << std::endl;

  std::cout << "Muestra round(3.4f): " << EngineUtilities::Math::round(3.4f) << std::endl;
  std::cout << "Muestra round(3.6f): " << EngineUtilities::Math::round(3.6f) << std::endl;
  std::cout << "Muestra round(3.5f): " << EngineUtilities::Math::round(3.5f) << std::endl; 
  std::cout << "Muestra round(-3.4f): " << EngineUtilities::Math::round(-3.4f) << std::endl;
  std::cout << "Muestra round(-3.6f): " << EngineUtilities::Math::round(-3.6f) << std::endl;
  std::cout << "Muestra round(-3.5f): " << EngineUtilities::Math::round(-3.5f) << std::endl;

  std::cout << "Muestra floor(5.7f): " << EngineUtilities::Math::floor(5.7f) << std::endl;
  std::cout << "Muestra floor(-5.7f): " << EngineUtilities::Math::floor(-5.7f) << std::endl;
  std::cout << "Muestra ceil(5.2f): " << EngineUtilities::Math::ceil(5.2f) << std::endl;
  std::cout << "Muestra ceil(-5.2f): " << EngineUtilities::Math::ceil(-5.2f) << std::endl;




  float angle_90_deg = EngineUtilities::Math::radians(90.0f);
  float angle_0_deg = EngineUtilities::Math::radians(0.0f);
  float angle_30_deg = EngineUtilities::Math::radians(30.0f);
  float angle_180_deg = EngineUtilities::Math::radians(180.0f);

  std::cout << "Muestra sin(90 deg): " << EngineUtilities::Math::sin(angle_90_deg) << " (esperado 1.0000)" << std::endl;
  std::cout << "Muestra cos(90 deg): " << EngineUtilities::Math::cos(angle_90_deg) << " (esperado 0.0000)" << std::endl;
  std::cout << "Muestra sin(0 deg): " << EngineUtilities::Math::sin(angle_0_deg) << " (esperado 0.0000)" << std::endl;
  std::cout << "Muestra cos(0 deg): " << EngineUtilities::Math::cos(angle_0_deg) << " (esperado 1.0000)" << std::endl;
  std::cout << "Muestra sin(30 deg): " << EngineUtilities::Math::sin(angle_30_deg) << " (esperado 0.5000)" << std::endl;
  std::cout << "Muestra cos(30 deg): " << EngineUtilities::Math::cos(angle_30_deg) << " (esperado 0.8660)" << std::endl;
  std::cout << "Muestra sin(180 deg): " << EngineUtilities::Math::sin(angle_180_deg) << " (esperado 0.0000)" << std::endl;
  std::cout << "Muestra cos(180 deg): " << EngineUtilities::Math::cos(angle_180_deg) << " (esperado -1.0000)" << std::endl;

  std::cout << "\n--- Pruebas de Math Inverse Trig ---\n";
  std::cout << "Muestra asin(0.5): " << EngineUtilities::Math::degrees(EngineUtilities::Math::asin(0.5f)) << " deg (esperado 30.0000)\n";
  std::cout << "Muestra acos(0.5): " << EngineUtilities::Math::degrees(EngineUtilities::Math::acos(0.5f)) << " deg (esperado 60.0000)\n";
  std::cout << "Muestra atan(1.0): " << EngineUtilities::Math::degrees(EngineUtilities::Math::atan(1.0f)) << " deg (esperado 45.0000)\n";
  std::cout << "Muestra atan2(1, 1): " << EngineUtilities::Math::degrees(EngineUtilities::Math::atan2(1.0f, 1.0f)) << " deg (esperado 45.0000)\n";
  std::cout << "Muestra atan2(1, -1): " << EngineUtilities::Math::degrees(EngineUtilities::Math::atan2(1.0f, -1.0f)) << " deg (esperado 135.0000)\n";
  std::cout << "Muestra atan2(-1, -1): " << EngineUtilities::Math::degrees(EngineUtilities::Math::atan2(-1.0f, -1.0f)) << " deg (esperado -135.0000)\n";
  std::cout << "Muestra atan2(-1, 1): " << EngineUtilities::Math::degrees(EngineUtilities::Math::atan2(-1.0f, 1.0f)) << " deg (esperado -45.0000)\n";
  std::cout << "Muestra atan2(1, 0): " << EngineUtilities::Math::degrees(EngineUtilities::Math::atan2(1.0f, 0.0f)) << " deg (esperado 90.0000)\n";
  std::cout << "Muestra atan2(-1, 0): " << EngineUtilities::Math::degrees(EngineUtilities::Math::atan2(-1.0f, 0.0f)) << " deg (esperado -90.0000)\n";


  std::cout << "\n--- Quaternion ---" << std::endl;

  
  EngineUtilities::Rotations::Quaternion q_identity = EngineUtilities::Rotations::Quaternion::Identity();
  std::cout << "\nIdentidad: " << q_identity << std::endl;

  
  EngineUtilities::Vectors::Vector3 axis_y = EngineUtilities::Vectors::Vector3::UnitY();
  float angle_90_rad = EngineUtilities::Math::radians(90.0f);
  EngineUtilities::Rotations::Quaternion q_rot_y_90(axis_y, angle_90_rad);
  std::cout << "Rotacion Y 90 : " << q_rot_y_90 << std::endl;

 
  EngineUtilities::Vectors::Vector3 vec_to_rotate(1.0f, 0.0f, 0.0f); 
  EngineUtilities::Vectors::Vector3 rotated_vec = q_rot_y_90 * vec_to_rotate;
  std::cout << "Vector original: " << vec_to_rotate << std::endl;
  std::cout << "Vector rotado por Q_rot_y_90: " << rotated_vec << std::endl;


  EngineUtilities::Vectors::Vector3 axis_z = EngineUtilities::Vectors::Vector3::UnitZ();
  float angle_45_rad = EngineUtilities::Math::radians(45.0f);
  EngineUtilities::Rotations::Quaternion q_rot_z_45(axis_z, angle_45_rad);

  std::cout << "\nRotacion Z 45 g: " << q_rot_z_45 << std::endl;

  EngineUtilities::Rotations::Quaternion q_combined = q_rot_y_90 * q_rot_z_45;
  std::cout << "Q_rot_y_90 * Q_rot_z_45: " << q_combined << std::endl;


  EngineUtilities::Rotations::Quaternion q_inv = q_rot_y_90.inverse();
  EngineUtilities::Rotations::Quaternion q_conj = q_rot_y_90.conjugate();
  std::cout << "Q_rot_y_90 inversa: " << q_inv << std::endl;
  std::cout << "Q_rot_y_90 conjugado: " << q_conj << std::endl;
  std::cout << "Q_rot_y_90 * Q_rot_y_90.inverse() (debe ser identidad): " << (q_rot_y_90 * q_inv) << std::endl;


  EngineUtilities::Rotations::Quaternion q_unnormalized(1.0f, 2.0f, 3.0f, 4.0f);
  std::cout << "Cuaternion no normalizado: " << q_unnormalized << std::endl;
  std::cout << "Cuaternion normalizado: " << q_unnormalized.normalized() << std::endl;
  std::cout << "Magnitud del normalizado: " << q_unnormalized.normalized().magnitude() << std::endl;


  EngineUtilities::Rotations::Quaternion slerped_q = EngineUtilities::Rotations::Quaternion::Slerp(q_identity, q_rot_y_90, 0.5f);
  std::cout << "SLERP (0.5) de identidad a Rotacion Y 90: " << slerped_q << std::endl;
  EngineUtilities::Vectors::Vector3 slerped_vec_rot = slerped_q * EngineUtilities::Vectors::Vector3(1.0f, 0.0f, 0.0f);
  std::cout << "Vector (1,0,0) rotado por SLERP: " << slerped_vec_rot << std::endl;



  std::cout << "\n--- Cuaternion <-> Matriz4x4 Conversion ---" << std::endl;

  EngineUtilities::Rotations::Quaternion q_from_axis_angle(
    EngineUtilities::Vectors::Vector3(0.707f, 0.707f, 0.0f).normalize(),
    EngineUtilities::Math::radians(90.0f)
  );
  std::cout << "Cuaternión de eje-ángulo (90 grados alrededor de (1,1,0) normalizado):\n" << q_from_axis_angle << std::endl;

  EngineUtilities::Matrices::Matriz4x4 mat_from_q = q_from_axis_angle.toMatrix4x4();
  std::cout << "Matriz 4x4 convertida de cuaternión:\n" << mat_from_q << std::endl;

  EngineUtilities::Rotations::Quaternion q_from_mat = EngineUtilities::Rotations::Quaternion::fromMatrix4x4(mat_from_q);
  std::cout << "Cuaternión convertido de la matriz:\n" << q_from_mat << std::endl;


  EngineUtilities::Vectors::Vector3 extracted_axis;
  float extracted_angle;
  q_from_axis_angle.toAxisAngle(extracted_axis, extracted_angle);
  std::cout << "Cuaternión original (" << q_from_axis_angle << ") -> Eje: " << extracted_axis
    << ", Angulo: " << EngineUtilities::Math::degrees(extracted_angle) << " deg" << std::endl;

  return 0;
}