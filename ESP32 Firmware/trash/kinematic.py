import math


def normalize_angle(angle: int):
	if angle < 0:
		print('Wrong angle:', angle)
		return 0
	elif angle > 180:
		print('Wrong angle:', angle)
		return 180

	return angle


coxa_length = 27.5
femur_length = 55
tibia_length = 80

x = coxa_length + femur_length  # 82.5
y = 0
z = 60

# Calculate the coxa angle (degree)
coxa_angle = int(math.atan2(y, x) * (180 / math.pi))
print("[*] coxa_angle:", coxa_angle)

# Calculate the distance from the coxa to the foot in the horizontal plane
horizontal_distance = math.sqrt(x * x + y * y)
print("[*] horizontal_distance:", horizontal_distance)

horizontal_femur_tibia_distance = horizontal_distance - coxa_length

# Calculate the distance from the coxa to the foot
coxa_to_foot_distance = math.sqrt(horizontal_femur_tibia_distance * horizontal_femur_tibia_distance + z * z)
print("[*] coxa_to_foot_distance:", coxa_to_foot_distance)

# Calculate the angle between the femur and tibia (radian)
femur_tibia_angle = math.acos((femur_length * femur_length + tibia_length * tibia_length - coxa_to_foot_distance * coxa_to_foot_distance) / (2 * femur_length * tibia_length))
print("[*] femur_tibia_angle:", femur_tibia_angle)

# Calculate the tibia angle (degree)
tibia_angle = int(femur_tibia_angle * (180 / math.pi)) # 180 - femur_tibia_angle * (180 / math.pi)
print("[*] tibia_angle:", tibia_angle)

# Calculate the angle between the horizontal plane and the line between the coxa and the foot (radian)
foot_angle = math.atan2(horizontal_femur_tibia_distance, z)
print("[*] foot_angle:", foot_angle)

# Calculate the angle between the femur and the line between the coxa and the foot (radian)
femur_foot_angle = math.acos((femur_length * femur_length - tibia_length * tibia_length + coxa_to_foot_distance * coxa_to_foot_distance) / (2 * femur_length * coxa_to_foot_distance))
print("[*] femur_foot_angle:", femur_foot_angle)

# Calculate the femur angle (degree)
femur_angle = int((foot_angle + femur_foot_angle) * (180 / math.pi))
print("[*] femur_angle:", femur_angle)

print('Default angles:', coxa_angle, femur_angle, tibia_angle)

normalized_coxa_angle = normalize_angle(coxa_angle)
normalized_femur_angle = normalize_angle(femur_angle)
normalized_tibia_angle = normalize_angle(tibia_angle)

print('Normalized angles:', normalized_coxa_angle, normalized_femur_angle, normalized_tibia_angle)

print('Final angles:', coxa_angle + 90, 270 - femur_angle, tibia_angle)  # 180 => 180 - femur_angle + 90
