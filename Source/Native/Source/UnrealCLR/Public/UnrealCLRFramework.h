/*
 * Copyright (c) 2020 Stanislav Denisov (nxrighthere@gmail.com)
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 3 with a static linking exception which accompanies this
 * distribution.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 */

#pragma once

UNREALCLR_API DECLARE_LOG_CATEGORY_EXTERN(LogUnrealAssert, Log, All);
UNREALCLR_API DECLARE_LOG_CATEGORY_EXTERN(LogUnrealManaged, Log, All);

namespace UnrealCLRFramework {
	using AnimationMode = EAnimationMode::Type;
	using CameraProjectionMode = ECameraProjectionMode::Type;
	using CollisionMode = ECollisionEnabled::Type;
	using CollisionShapeType = ECollisionShape::Type;
	using ComponentMobility = EComponentMobility::Type;
	using WindowMode = EWindowMode::Type;

	using AudioFadeCurve = EAudioFaderCurve;
	using BlendType = EViewTargetBlendFunction;
	using CollisionChannel = ECollisionChannel;
	using CollisionResponse = ECollisionResponse;
	using ControllerHand = EControllerHand;
	using InputEvent = EInputEvent;
	using NetMode = ENetMode;

	using CollisionShape = FCollisionShape;

	enum struct LogLevel : int32 {
		Display,
		Warning,
		Error,
		Fatal
	};

	enum struct AttachmentTransformRule : int32 {
		KeepRelativeTransform,
		KeepWorldTransform,
		SnapToTargetIncludingScale,
		SnapToTargetNotIncludingScale
	};

	enum struct DetachmentTransformRule : int32 {
		KeepRelativeTransform,
		KeepWorldTransform
	};

	enum struct TeleportType : int32 {
		None,
		TeleportPhysics,
		ResetPhysics
	};

	enum struct UpdateTransformFlags : int32 {
		None = 0,
		SkipPhysicsUpdate = 1 << 0,
		PropagateFromParent = 1 << 1,
		OnlyUpdateIfUsingSocket = 1 << 2
	};

	enum struct AIFocusPriority : int32 {
		Default = 0,
		Move = 1,
		Gameplay = 2
	};

	struct Color {
		uint8 B;
		uint8 G;
		uint8 R;
		uint8 A;

		FORCEINLINE Color(FColor Value) {
			R = Value.R;
			G = Value.G;
			B = Value.B;
			A = Value.A;
		}

		FORCEINLINE operator FColor() const { return FColor(R, G, B, A); }
	};

	struct Vector2 {
		float X;
		float Y;

		FORCEINLINE Vector2(FVector2D Value) {
			X = Value.X;
			Y = Value.Y;
		}

		FORCEINLINE operator FVector2D() const { return FVector2D(X, Y); }
	};

	struct Vector3 {
		float X;
		float Y;
		float Z;

		FORCEINLINE Vector3(FVector Value) {
			X = Value.X;
			Y = Value.Y;
			Z = Value.Z;
		}

		FORCEINLINE operator FVector() const { return FVector(X, Y, Z); }
	};

	struct Quaternion {
		float X;
		float Y;
		float Z;
		float W;

		FORCEINLINE Quaternion(FQuat Value) {
			X = Value.X;
			Y = Value.Y;
			Z = Value.Z;
			W = Value.W;
		}

		FORCEINLINE operator FQuat() const { return FQuat(X, Y, Z, W); }
	};

	struct LinearColor {
		float R;
		float G;
		float B;
		float A;

		FORCEINLINE LinearColor(FLinearColor Value) {
			R = Value.R;
			G = Value.G;
			B = Value.B;
			A = Value.A;
		}

		FORCEINLINE operator FLinearColor() const { return FLinearColor(R, G, B, A); }
	};

	struct Transform {
		Quaternion Rotation;
		Vector3 Location;
		Vector3 Scale;

		FORCEINLINE Transform(const FTransform& Value) :
			Rotation(Value.GetRotation()),
			Location(Value.GetTranslation()),
			Scale(Value.GetScale3D()) { }

		FORCEINLINE operator FTransform() const { return FTransform(Rotation, Location, Scale); }
	};

	struct Hit {
		Vector3 Location;
		Vector3 ImpactLocation;
		Vector3 Normal;
		Vector3 ImpactNormal;
		Vector3 TraceStart;
		Vector3 TraceEnd;
		AActor* Actor;
		float Time;
		float Distance;
		float PenetrationDepth;
		bool BlockingHit;
		bool StartPenetrating;

		FORCEINLINE Hit(const FHitResult& Value) :
			Location(FVector(Value.Location.X, Value.Location.Y, Value.Location.Z)),
			ImpactLocation(FVector(Value.ImpactPoint.X, Value.ImpactPoint.Y, Value.ImpactPoint.Z)),
			Normal(FVector(Value.Normal.X, Value.Normal.Y, Value.Normal.Z)),
			ImpactNormal(FVector(Value.ImpactNormal.X, Value.ImpactNormal.Y, Value.ImpactNormal.Z)),
			TraceStart(FVector(Value.TraceStart.X, Value.TraceStart.Y, Value.TraceStart.Z)),
			TraceEnd(FVector(Value.TraceEnd.X, Value.TraceEnd.Y, Value.TraceEnd.Z)),
			Actor(Value.GetActor()),
			Time(Value.Time),
			Distance(Value.Distance),
			PenetrationDepth(Value.PenetrationDepth),
			BlockingHit(Value.bBlockingHit),
			StartPenetrating(Value.bStartPenetrating) { }
	};

	typedef void (*InputDelegate)();

	typedef void (*InputAxisDelegate)(float);

	typedef void (*ConsoleVariableDelegate)();

	typedef void (*ConsoleCommandDelegate)(float);

	// Enumerable

	enum struct ObjectType : int32 {
		Blueprint,
		SoundWave,
		AnimationSequence,
		AnimationMontage,
		StaticMesh,
		SkeletalMesh,
		Material,
		Texture2D
	};

	enum struct ActorType : int32 {
		Base,
		Camera,
		TriggerBox,
		TriggerSphere,
		TriggerCapsule,
		Pawn,
		Character,
		AIController,
		PlayerController,
		Brush,
		AmbientSound,
		DirectionalLight,
		PointLight,
		RectLight,
		SpotLight,
		TriggerVolume,
		PostProcessVolume
	};

	enum struct ComponentType : int32 {
		// Non-attachable
		Actor,
		Input,
		// Attachable
		Scene,
		Audio,
		Camera,
		Light,
		DirectionalLight,
		MotionController,
		StaticMesh,
		InstancedStaticMesh,
		ChildActor,
		Box,
		Sphere,
		Capsule,
		SkeletalMesh,
		RadialForce
	};

	// Non-instantiable

	namespace Assert {
		static void OutputMessage(const char* Message);
	}

	namespace CommandLine {
		static void Get(char* Arguments);
		static void Set(const char* Arguments);
		static void Append(const char* Arguments);
	}

	namespace Debug {
		static void Log(LogLevel Level, const char* Message);
		static void HandleException(const char* Exception);
		static void AddOnScreenMessage(int32 Key, float TimeToDisplay, Color DisplayColor, const char* Message);
		static void ClearOnScreenMessages();
		static void DrawBox(const Vector3* Center, const Vector3* Extent, const Quaternion* Rotation, Color Color, bool PersistentLines, float LifeTime, uint8 DepthPriority, float Thickness);
		static void DrawCapsule(const Vector3* Center, float HalfHeight, float Radius, const Quaternion* Rotation, Color Color, bool PersistentLines, float LifeTime, uint8 DepthPriority, float Thickness);
		static void DrawCone(const Vector3* Origin, const Vector3* Direction, float Length, float AngleWidth, float AngleHeight, int32 Sides, Color Color, bool PersistentLines, float LifeTime, uint8 DepthPriority, float Thickness);
		static void DrawCylinder(const Vector3* Start, const Vector3* End, float Radius, int32 Segments, Color Color, bool PersistentLines, float LifeTime, uint8 DepthPriority, float Thickness);
		static void DrawSphere(const Vector3* Center, float Radius, int32 Segments, Color Color, bool PersistentLines, float LifeTime, uint8 DepthPriority, float Thickness);
		static void DrawLine(const Vector3* Start, const Vector3* End, Color Color, bool PersistentLines, float LifeTime, uint8 DepthPriority, float Thickness);
		static void DrawPoint(const Vector3* Location, float Size, Color Color, bool PersistentLines, float LifeTime, uint8 DepthPriority);
		static void FlushPersistentLines();
	}

	namespace Object {
		static bool IsPendingKill(UObject* Object);
		static bool IsValid(UObject* Object);
		static UObject* Load(ObjectType Type, const char* Name);
		static void Rename(UObject* Object, const char* Name);
		static uint32 GetID(UObject* Object);
		static void GetName(UObject* Object, char* Name);
		static bool GetBool(UObject* Object, const char* Name, bool* value);
		static bool GetByte(UObject* Object, const char* Name, int8* Value);
		static bool GetShort(UObject* Object, const char* Name, int16* Value);
		static bool GetInt(UObject* Object, const char* Name, int32* Value);
		static bool GetLong(UObject* Object, const char* Name, int64* Value);
		static bool GetUShort(UObject* Object, const char* Name, uint16* Value);
		static bool GetUInt(UObject* Object, const char* Name, uint32* Value);
		static bool GetULong(UObject* Object, const char* Name, uint64* Value);
		static bool GetFloat(UObject* Object, const char* Name, float* Value);
		static bool GetDouble(UObject* Object, const char* Name, double* Value);
		static bool GetText(UObject* Object, const char* Name, char* Value);
		static bool SetBool(UObject* Object, const char* Name, bool value);
		static bool SetByte(UObject* Object, const char* Name, int8 Value);
		static bool SetShort(UObject* Object, const char* Name, int16 Value);
		static bool SetInt(UObject* Object, const char* Name, int32 Value);
		static bool SetLong(UObject* Object, const char* Name, int64 Value);
		static bool SetUShort(UObject* Object, const char* Name, uint16 Value);
		static bool SetUInt(UObject* Object, const char* Name, uint32 Value);
		static bool SetULong(UObject* Object, const char* Name, uint64 Value);
		static bool SetFloat(UObject* Object, const char* Name, float Value);
		static bool SetDouble(UObject* Object, const char* Name, double Value);
		static bool SetText(UObject* Object, const char* Name, const char* Value);
	}

	namespace Application {
		static bool IsCanEverRender();
		static bool IsPackagedForDistribution();
		static bool IsPackagedForShipping();
		static void GetProjectDirectory(char* Directory);
		static void GetDefaultLanguage(char* Language);
		static void GetProjectName(char* ProjectName);
		static float GetVolumeMultiplier();
		static void SetProjectName(const char* ProjectName);
		static void SetVolumeMultiplier(float Value);
		static void RequestExit(bool Force);
	}

	namespace ConsoleManager {
		static bool IsRegisteredVariable(const char* Name);
		static IConsoleVariable* FindVariable(const char* Name);
		static IConsoleVariable* RegisterVariableBool(const char* Name, const char* Help, bool DefaultValue, bool ReadOnly);
		static IConsoleVariable* RegisterVariableInt(const char* Name, const char* Help, int32 DefaultValue, bool ReadOnly);
		static IConsoleVariable* RegisterVariableFloat(const char* Name, const char* Help, float DefaultValue, bool ReadOnly);
		static IConsoleVariable* RegisterVariableString(const char* Name, const char* Help, const char* DefaultValue, bool ReadOnly);
		static void RegisterCommand(const char* Name, const char* Help, ConsoleCommandDelegate Function, bool ReadOnly);
		static void UnregisterObject(const char* Name);
	}

	namespace Engine {
		static bool IsSplitScreen();
		static bool IsEditor();
		static bool IsForegroundWindow();
		static bool IsExitRequested();
		static NetMode GetNetMode();
		static uint32 GetFrameNumber();
		static void GetViewportSize(Vector2* Value);
		static void GetScreenResolution(Vector2* Value);
		static WindowMode GetWindowMode();
		static void GetVersion(char* Version);
		static float GetMaxFPS();
		static void SetMaxFPS(float MaxFPS);
		static void SetTitle(const char* Title);
		static void AddActionMapping(const char* ActionName, const char* Key, bool Shift, bool Ctrl, bool Alt, bool Cmd);
		static void AddAxisMapping(const char* AxisName, const char* Key, float Scale);
		static void ForceGarbageCollection(bool FullPurge);
		static void DelayGarbageCollection();
	}

	namespace HeadMountedDisplay {
		static bool IsConnected();
		static bool GetEnabled();
		static bool GetLowPersistenceMode();
		static void GetDeviceName(char* Name);
		static void SetEnable(bool Value);
		static void SetLowPersistenceMode(bool Value);
	}

	namespace World {
		static bool GetSimulatePhysics();
		static int32 GetActorCount();
		static float GetDeltaSeconds();
		static float GetRealTimeSeconds();
		static float GetTimeSeconds();
		static void GetWorldOrigin(Vector3* Value);
		static AActor* GetActor(const char* Name, ActorType Type);
		static AActor* GetActorByTag(const char* Tag, ActorType Type);
		static AActor* GetActorByID(uint32 ID, ActorType Type);
		static APlayerController* GetFirstPlayerController();
		static void SetSimulatePhysics(bool Value);
		static void SetGravity(float Value);
		static bool SetWorldOrigin(const Vector3* Value);
		static bool LineTraceTestByChannel(const Vector3* Start, const Vector3* End, CollisionChannel Channel, bool TraceComplex, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool LineTraceTestByProfile(const Vector3* Start, const Vector3* End, const char* ProfileName, bool TraceComplex, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool LineTraceSingleByChannel(const Vector3* Start, const Vector3* End, CollisionChannel Channel, Hit* Hit, char* BoneName, bool TraceComplex, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool LineTraceSingleByProfile(const Vector3* Start, const Vector3* End, const char* ProfileName, Hit* Hit, char* BoneName, bool TraceComplex, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool SweepTestByChannel(const Vector3* Start, const Vector3* End, const Quaternion* Rotation, CollisionChannel Channel, const CollisionShape* Shape, bool TraceComplex, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool SweepTestByProfile(const Vector3* Start, const Vector3* End, const Quaternion* Rotation, const char* ProfileName, const CollisionShape* Shape, bool TraceComplex, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool SweepSingleByChannel(const Vector3* Start, const Vector3* End, const Quaternion* Rotation, CollisionChannel Channel, const CollisionShape* Shape, Hit* Hit, char* BoneName, bool TraceComplex, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool SweepSingleByProfile(const Vector3* Start, const Vector3* End, const Quaternion* Rotation, const char* ProfileName, const CollisionShape* Shape, Hit* Hit, char* BoneName, bool TraceComplex, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool OverlapAnyTestByChannel(const Vector3* Location, const Quaternion* Rotation, CollisionChannel Channel, const CollisionShape* Shape, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool OverlapAnyTestByProfile(const Vector3* Location, const Quaternion* Rotation, const char* ProfileName, const CollisionShape* Shape, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool OverlapBlockingTestByChannel(const Vector3* Location, const Quaternion* Rotation, CollisionChannel Channel, const CollisionShape* Shape, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
		static bool OverlapBlockingTestByProfile(const Vector3* Location, const Quaternion* Rotation, const char* ProfileName, const CollisionShape* Shape, AActor* IgnoredActor, UPrimitiveComponent* IgnoredComponent);
	}

	// Instantiable

	namespace Blueprint {
		static bool IsValidActorClass(UBlueprint* Blueprint, ActorType Type);
		static bool IsValidComponentClass(UBlueprint* Blueprint, ComponentType Type);
	}

	namespace ConsoleObject {
		static bool IsBool(IConsoleObject* ConsoleObject);
		static bool IsInt(IConsoleObject* ConsoleObject);
		static bool IsFloat(IConsoleObject* ConsoleObject);
		static bool IsString(IConsoleObject* ConsoleObject);
	}

	namespace ConsoleVariable {
		static bool GetBool(IConsoleVariable* ConsoleVariable);
		static int32 GetInt(IConsoleVariable* ConsoleVariable);
		static float GetFloat(IConsoleVariable* ConsoleVariable);
		static void GetString(IConsoleVariable* ConsoleVariable, char* Value);
		static void SetBool(IConsoleVariable* ConsoleVariable, bool Value);
		static void SetInt(IConsoleVariable* ConsoleVariable, int32 Value);
		static void SetFloat(IConsoleVariable* ConsoleVariable, float Value);
		static void SetString(IConsoleVariable* ConsoleVariable, const char* Value);
		static void SetOnChangedCallback(IConsoleVariable* ConsoleVariable, ConsoleVariableDelegate Function);
		static void ClearOnChangedCallback(IConsoleVariable* ConsoleVariable);
	}

	namespace Actor {
		static bool IsPendingKill(AActor* Actor);
		static bool IsRootComponentMovable(AActor* Actor);
		static bool IsOverlappingActor(AActor* Actor, AActor* Other);
		static AActor* Spawn(const char* Name, ActorType Type, UObject* Blueprint);
		static bool Destroy(AActor* Actor);
		static void Rename(AActor* Actor, const char* Name);
		static void Hide(AActor* Actor, bool Value);
		static bool TeleportTo(AActor* Actor, const Vector3* DestinationLocation, const Quaternion* DestinationRotation, bool IsATest, bool NoCheck);
		static UActorComponent* GetComponent(AActor* Actor, const char* Name, ComponentType Type);
		static UActorComponent* GetComponentByTag(AActor* Actor, const char* Tag, ComponentType Type);
		static UActorComponent* GetComponentByID(AActor* Actor, uint32 ID, ComponentType Type);
		static USceneComponent* GetRootComponent(AActor* Actor, ComponentType Type);
		static UInputComponent* GetInputComponent(AActor* Actor);
		static bool GetBlockInput(AActor* Actor);
		static float GetDistanceTo(AActor* Actor, AActor* Other);
		static void GetBounds(AActor* Actor, bool OnlyCollidingComponents, Vector3* Origin, Vector3* Extent);
		static bool SetRootComponent(AActor* Actor, USceneComponent* RootComponent);
		static void SetInputComponent(AActor* Actor, UInputComponent* InputComponent);
		static void SetBlockInput(AActor* Actor, bool Value);
		static void SetLifeSpan(AActor* Actor, float LifeSpan);
		static void SetEnableCollision(AActor* Actor, bool Value);
		static void AddTag(AActor* Actor, const char* Tag);
		static void RemoveTag(AActor* Actor, const char* Tag);
		static bool HasTag(AActor* Actor, const char* Tag);
	}

	namespace TriggerBase { }

	namespace TriggerBox { }

	namespace TriggerCapsule { }

	namespace TriggerSphere { }

	namespace Pawn {
		static void AddControllerYawInput(APawn* Pawn, float Value);
		static void AddControllerPitchInput(APawn* Pawn, float Value);
		static void AddControllerRollInput(APawn* Pawn, float Value);
		static void AddMovementInput(APawn* Pawn, const Vector3* WorldDirection, float ScaleValue, bool Force);
		static void GetGravityDirection(APawn* Pawn, Vector3* Value);
	}

	namespace Character {

	}

	namespace Controller {
		static bool IsLookInputIgnored(AController* Controller);
		static bool IsMoveInputIgnored(AController* Controller);
		static bool IsPlayerController(AController* Controller);
		static APawn* GetPawn(AController* Controller);
		static bool LineOfSightTo(AController* Controller, AActor* Actor, const Vector3* ViewPoint, bool AlternateChecks);
		static void SetInitialLocationAndRotation(AController* Controller, const Vector3* NewLocation, const Quaternion* NewRotation);
		static void SetIgnoreLookInput(AController* Controller, bool Value);
		static void SetIgnoreMoveInput(AController* Controller, bool Value);
		static void ResetIgnoreLookInput(AController* Controller);
		static void ResetIgnoreMoveInput(AController* Controller);
	}

	namespace AIController {
		static void ClearFocus(AAIController* AIController, AIFocusPriority Priority);
		static void GetFocalPoint(AAIController* AIController, Vector3* Value);
		static void SetFocalPoint(AAIController* AIController, const Vector3* NewFocus, AIFocusPriority Priority);
		static AActor* GetFocusActor(AAIController* AIController);
		static bool GetAllowStrafe(AAIController* AIController);
		static void SetAllowStrafe(AAIController* AIController, bool Value);
		static void SetFocus(AAIController* AIController, AActor* NewFocus, AIFocusPriority Priority);
	}

	namespace PlayerController {
		static bool IsPaused(APlayerController* PlayerController);
		static bool GetShowMouseCursor(APlayerController* PlayerController);
		static bool GetMousePosition(APlayerController* PlayerController, float* X, float* Y);
		static void GetPlayerViewPoint(APlayerController* PlayerController, Vector3* Location, Quaternion* Rotation);
		static UPlayerInput* GetPlayerInput(APlayerController* PlayerController);
		static void SetShowMouseCursor(APlayerController* PlayerController, bool Value);
		static void SetMousePosition(APlayerController* PlayerController, float X, float Y);
		static void ConsoleCommand(APlayerController* PlayerController, const char* Command, bool WriteToLog);
		static bool SetPause(APlayerController* PlayerController, bool Value);
		static void SetViewTarget(APlayerController* PlayerController, AActor* NewViewTarget);
		static void SetViewTargetWithBlend(APlayerController* PlayerController, AActor* NewViewTarget, float Time, float Exponent, BlendType Type, bool LockOutgoing);
		static void AddYawInput(APlayerController* PlayerController, float Value);
		static void AddPitchInput(APlayerController* PlayerController, float Value);
		static void AddRollInput(APlayerController* PlayerController, float Value);
	}

	namespace Volume {
		static bool EncompassesPoint(AVolume* Volume, const Vector3* Point, float SphereRadius, float* OutDistanceToPoint);
	}

	namespace TriggerVolume { }

	namespace PostProcessVolume {
		static bool GetEnabled(APostProcessVolume* PostProcessVolume);
		static float GetBlendRadius(APostProcessVolume* PostProcessVolume);
		static float GetBlendWeight(APostProcessVolume* PostProcessVolume);
		static bool GetUnbound(APostProcessVolume* PostProcessVolume);
		static float GetPriority(APostProcessVolume* PostProcessVolume);
		static void SetEnabled(APostProcessVolume* PostProcessVolume, bool Value);
		static void SetBlendRadius(APostProcessVolume* PostProcessVolume, float Value);
		static void SetBlendWeight(APostProcessVolume* PostProcessVolume, float Value);
		static void SetUnbound(APostProcessVolume* PostProcessVolume, bool Value);
		static void SetPriority(APostProcessVolume* PostProcessVolume, float Priority);
	}

	namespace AmbientSound { }

	namespace Light { }

	namespace DirectionalLight { }

	namespace PointLight { }

	namespace RectLight { }

	namespace SpotLight { }

	namespace SoundBase {
		static float GetDuration(USoundBase* SoundBase);
	}

	namespace SoundWave {
		static bool GetLoop(USoundWave* SoundWave);
		static void SetLoop(USoundWave* SoundWave, bool Value);
	}

	namespace AnimationAsset {

	}

	namespace AnimationSequenceBase {

	}

	namespace AnimationSequence {

	}

	namespace AnimationCompositeBase {

	}

	namespace AnimationMontage {

	}

	namespace AnimationInstance {
		static UAnimMontage* GetCurrentActiveMontage(UAnimInstance* AnimationInstance);
		static bool IsPlaying(UAnimInstance* AnimationInstance, UAnimMontage* Montage);
		static float GetPlayRate(UAnimInstance* AnimationInstance, UAnimMontage* Montage);
		static float GetPosition(UAnimInstance* AnimationInstance, UAnimMontage* Montage);
		static float GetBlendTime(UAnimInstance* AnimationInstance, UAnimMontage* Montage);
		static void GetCurrentSection(UAnimInstance* AnimationInstance, UAnimMontage* Montage, char* SectionName);
		static void SetPlayRate(UAnimInstance* AnimationInstance, UAnimMontage* Montage, float Value);
		static void SetPosition(UAnimInstance* AnimationInstance, UAnimMontage* Montage, float Position);
		static void SetNextSection(UAnimInstance* AnimationInstance, UAnimMontage* Montage, const char* SectionToChange, const char* NextSection);
		static float PlayMontage(UAnimInstance* AnimationInstance, UAnimMontage* Montage, float PlayRate, float TimeToStartMontageAt, bool StopAllMontages);
		static void PauseMontage(UAnimInstance* AnimationInstance, UAnimMontage* Montage);
		static void ResumeMontage(UAnimInstance* AnimationInstance, UAnimMontage* Montage);
		static void StopMontage(UAnimInstance* AnimationInstance, UAnimMontage* Montage, float BlendOutTime);
		static void JumpToSection(UAnimInstance* AnimationInstance, UAnimMontage* Montage, const char* SectionName);
		static void JumpToSectionsEnd(UAnimInstance* AnimationInstance, UAnimMontage* Montage, const char* SectionName);
	}

	namespace Player {

	}

	namespace PlayerInput {
		static bool IsKeyPressed(UPlayerInput* PlayerInput, const char* Key);
		static float GetTimeKeyPressed(UPlayerInput* PlayerInput, const char* Key);
		static void GetMouseSensitivity(UPlayerInput* PlayerInput, Vector2* Value);
		static void SetMouseSensitivity(UPlayerInput* PlayerInput, const Vector2* Value);
	}

	namespace StreamableRenderAsset {

	}

	namespace StaticMesh {

	}

	namespace SkeletalMesh {

	}

	namespace Texture {

	}

	namespace Texture2D {
		static void GetSize(UTexture2D* Texture2D, Vector2* Value);
	}

	namespace ActorComponent {
		static bool IsOwnerSelected(UActorComponent* ActorComponent);
		static AActor* GetOwner(UActorComponent* ActorComponent);
		static void Destroy(UActorComponent* ActorComponent, bool PromoteChildren);
		static void AddTag(UActorComponent* ActorComponent, const char* Tag);
		static void RemoveTag(UActorComponent* ActorComponent, const char* Tag);
		static bool HasTag(UActorComponent* ActorComponent, const char* Tag);
	}

	namespace InputComponent {
		static bool HasBindings(UInputComponent* InputComponent);
		static int32 GetActionBindingsNumber(UInputComponent* InputComponent);
		static void ClearActionBindings(UInputComponent* InputComponent);
		static void BindAction(UInputComponent* InputComponent, const char* ActionName, InputEvent KeyEvent, bool ExecutedWhenPaused, InputDelegate Function);
		static void BindAxis(UInputComponent* InputComponent, const char* AxisName, bool ExecutedWhenPaused, InputAxisDelegate Function);
		static void RemoveActionBinding(UInputComponent* InputComponent, const char* ActionName, InputEvent KeyEvent);
		static bool GetBlockInput(UInputComponent* InputComponent);
		static void SetBlockInput(UInputComponent* InputComponent, bool Value);
		static int32 GetPriority(UInputComponent* InputComponent);
		static void SetPriority(UInputComponent* InputComponent, int32 Value);
	}

	namespace SceneComponent {
		static bool IsAttachedToComponent(USceneComponent* SceneComponent, USceneComponent* Component);
		static bool IsAttachedToActor(USceneComponent* SceneComponent, AActor* Actor);
		static bool IsSocketExists(USceneComponent* SceneComponent, const char* SocketName);
		static bool HasAnySockets(USceneComponent* SceneComponent);
		static USceneComponent* Create(AActor* Actor, ComponentType Type, const char* Name, bool SetAsRoot, UObject* Blueprint);
		static bool AttachToComponent(USceneComponent* SceneComponent, USceneComponent* Parent, AttachmentTransformRule AttachmentRule, const char* SocketName);
		static void DetachFromComponent(USceneComponent* SceneComponent, DetachmentTransformRule DetachmentRule);
		static void Activate(USceneComponent* SceneComponent);
		static void Deactivate(USceneComponent* SceneComponent);
		static void UpdateToWorld(USceneComponent* SceneComponent, TeleportType Type, UpdateTransformFlags Flags);
		static void AddLocalOffset(USceneComponent* SceneComponent, const Vector3* DeltaLocation);
		static void AddLocalRotation(USceneComponent* SceneComponent, const Quaternion* DeltaRotation);
		static void AddRelativeLocation(USceneComponent* SceneComponent, const Vector3* DeltaLocation);
		static void AddRelativeRotation(USceneComponent* SceneComponent, const Quaternion* DeltaRotation);
		static void AddLocalTransform(USceneComponent* SceneComponent, const Transform* DeltaTransform);
		static void AddWorldOffset(USceneComponent* SceneComponent, const Vector3* DeltaLocation);
		static void AddWorldRotation(USceneComponent* SceneComponent, const Quaternion* DeltaRotation);
		static void AddWorldTransform(USceneComponent* SceneComponent, const Transform* DeltaTransform);
		static void GetAttachedSocketName(USceneComponent* SceneComponent, char* SocketName);
		static void GetSocketLocation(USceneComponent* SceneComponent, const char* SocketName, Vector3* Value);
		static void GetSocketRotation(USceneComponent* SceneComponent, const char* SocketName, Quaternion* Value);
		static void GetComponentVelocity(USceneComponent* SceneComponent, Vector3* Value);
		static void GetComponentLocation(USceneComponent* SceneComponent, Vector3* Value);
		static void GetComponentRotation(USceneComponent* SceneComponent, Quaternion* Value);
		static void GetComponentScale(USceneComponent* SceneComponent, Vector3* Value);
		static void GetComponentTransform(USceneComponent* SceneComponent, Transform* Value);
		static void GetForwardVector(USceneComponent* SceneComponent, Vector3* Value);
		static void GetRightVector(USceneComponent* SceneComponent, Vector3* Value);
		static void GetUpVector(USceneComponent* SceneComponent, Vector3* Value);
		static void SetMobility(USceneComponent* SceneComponent, ComponentMobility Mobility);
		static void SetRelativeLocation(USceneComponent* SceneComponent, const Vector3* Location);
		static void SetRelativeRotation(USceneComponent* SceneComponent, const Quaternion* Rotation);
		static void SetRelativeTransform(USceneComponent* SceneComponent, const Transform* Transform);
		static void SetWorldLocation(USceneComponent* SceneComponent, const Vector3* Location);
		static void SetWorldRotation(USceneComponent* SceneComponent, const Quaternion* Rotation);
		static void SetWorldScale(USceneComponent* SceneComponent, const Vector3* Scale);
		static void SetWorldTransform(USceneComponent* SceneComponent, const Transform* Transform);
	}

	namespace AudioComponent {
		static bool IsPlaying(UAudioComponent* AudioComponent);
		static bool GetPaused(UAudioComponent* AudioComponent);
		static void SetSound(UAudioComponent* AudioComponent, USoundBase* Sound);
		static void SetPaused(UAudioComponent* AudioComponent, bool Value);
		static void Play(UAudioComponent* AudioComponent);
		static void Stop(UAudioComponent* AudioComponent);
		static void FadeIn(UAudioComponent* AudioComponent, float Duration, float VolumeLevel, float StartTime, AudioFadeCurve FadeCurve);
		static void FadeOut(UAudioComponent* AudioComponent, float Duration, float VolumeLevel, AudioFadeCurve FadeCurve);
	}

	namespace CameraComponent {
		static bool GetConstrainAspectRatio(UCameraComponent* CameraComponent);
		static float GetAspectRatio(UCameraComponent* CameraComponent);
		static float GetFieldOfView(UCameraComponent* CameraComponent);
		static float GetOrthoFarClipPlane(UCameraComponent* CameraComponent);
		static float GetOrthoNearClipPlane(UCameraComponent* CameraComponent);
		static float GetOrthoWidth(UCameraComponent* CameraComponent);
		static bool GetLockToHeadMountedDisplay(UCameraComponent* CameraComponent);
		static void SetProjectionMode(UCameraComponent* CameraComponent, CameraProjectionMode Mode);
		static void SetConstrainAspectRatio(UCameraComponent* CameraComponent, bool Value);
		static void SetAspectRatio(UCameraComponent* CameraComponent, float Value);
		static void SetFieldOfView(UCameraComponent* CameraComponent, float Value);
		static void SetOrthoFarClipPlane(UCameraComponent* CameraComponent, float Value);
		static void SetOrthoNearClipPlane(UCameraComponent* CameraComponent, float Value);
		static void SetOrthoWidth(UCameraComponent* CameraComponent, float Value);
		static void SetLockToHeadMountedDisplay(UCameraComponent* CameraComponent, bool Value);
	}

	namespace ChildActorComponent {
		static AActor* SetChildActor(UChildActorComponent* ChildActorComponent, ActorType Type);
	}

	namespace PrimitiveComponent {
		static bool IsGravityEnabled(UPrimitiveComponent* PrimitiveComponent);
		static void AddAngularImpulseInDegrees(UPrimitiveComponent* PrimitiveComponent, const Vector3* Impulse, const char* BoneName, bool VelocityChange);
		static void AddAngularImpulseInRadians(UPrimitiveComponent* PrimitiveComponent, const Vector3* Impulse, const char* BoneName, bool VelocityChange);
		static void AddForce(UPrimitiveComponent* PrimitiveComponent, const Vector3* Force, const char* BoneName, bool AccelerationChange);
		static void AddForceAtLocation(UPrimitiveComponent* PrimitiveComponent, const Vector3* Force, const Vector3* Location, const char* BoneName, bool LocalSpace);
		static void AddImpulse(UPrimitiveComponent* PrimitiveComponent, const Vector3* Impulse, const char* BoneName, bool VelocityChange);
		static void AddImpulseAtLocation(UPrimitiveComponent* PrimitiveComponent, const Vector3* Impulse, const Vector3* Location, const char* BoneName);
		static void AddRadialForce(UPrimitiveComponent* PrimitiveComponent, const Vector3* Origin, float Radius, float Strength, bool LinearFalloff, bool AccelerationChange);
		static void AddRadialImpulse(UPrimitiveComponent* PrimitiveComponent, const Vector3* Origin, float Radius, float Strength, bool LinearFalloff, bool AccelerationChange);
		static void AddTorqueInDegrees(UPrimitiveComponent* PrimitiveComponent, const Vector3* Torque, const char* BoneName, bool AccelerationChange);
		static void AddTorqueInRadians(UPrimitiveComponent* PrimitiveComponent, const Vector3* Torque, const char* BoneName, bool AccelerationChange);
		static float GetMass(UPrimitiveComponent* PrimitiveComponent);
		static bool GetCastShadow(UPrimitiveComponent* PrimitiveComponent);
		static bool GetOnlyOwnerSee(UPrimitiveComponent* PrimitiveComponent);
		static bool GetOwnerNoSee(UPrimitiveComponent* PrimitiveComponent);
		static UMaterialInstanceDynamic* GetMaterial(UPrimitiveComponent* PrimitiveComponent, int32 ElementIndex);
		static int32 GetMaterialsNumber(UPrimitiveComponent* PrimitiveComponent);
		static float GetDistanceToCollision(UPrimitiveComponent* PrimitiveComponent, const Vector3* Point, Vector3* ClosestPointOnCollision);
		static bool GetSquaredDistanceToCollision(UPrimitiveComponent* PrimitiveComponent, const Vector3* Point, float* SquaredDistance, Vector3* ClosestPointOnCollision);
		static float GetAngularDamping(UPrimitiveComponent* PrimitiveComponent);
		static float GetLinearDamping(UPrimitiveComponent* PrimitiveComponent);
		static void SetMass(UPrimitiveComponent* PrimitiveComponent, float Mass, const char* BoneName);
		static void SetCenterOfMass(UPrimitiveComponent* PrimitiveComponent, const Vector3* Offset, const char* BoneName);
		static void SetPhysicsLinearVelocity(UPrimitiveComponent* PrimitiveComponent, const Vector3* Velocity, bool AddToCurrent, const char* BoneName);
		static void SetPhysicsAngularVelocityInDegrees(UPrimitiveComponent* PrimitiveComponent, const Vector3* AngularVelocity, bool AddToCurrent, const char* BoneName);
		static void SetPhysicsAngularVelocityInRadians(UPrimitiveComponent* PrimitiveComponent, const Vector3* AngularVelocity, bool AddToCurrent, const char* BoneName);
		static void SetPhysicsMaxAngularVelocityInDegrees(UPrimitiveComponent* PrimitiveComponent, float MaxAngularVelocity, bool AddToCurrent, const char* BoneName);
		static void SetPhysicsMaxAngularVelocityInRadians(UPrimitiveComponent* PrimitiveComponent, float MaxAngularVelocity, bool AddToCurrent, const char* BoneName);
		static void SetCastShadow(UPrimitiveComponent* PrimitiveComponent, bool Value);
		static void SetOnlyOwnerSee(UPrimitiveComponent* PrimitiveComponent, bool Value);
		static void SetOwnerNoSee(UPrimitiveComponent* PrimitiveComponent, bool Value);
		static void SetMaterial(UPrimitiveComponent* PrimitiveComponent, int32 ElementIndex, UMaterialInterface* Material);
		static void SetSimulatePhysics(UPrimitiveComponent* PrimitiveComponent, bool Value);
		static void SetAngularDamping(UPrimitiveComponent* PrimitiveComponent, float Value);
		static void SetLinearDamping(UPrimitiveComponent* PrimitiveComponent, float Value);
		static void SetEnableGravity(UPrimitiveComponent* PrimitiveComponent, bool Value);
		static void SetCollisionMode(UPrimitiveComponent* PrimitiveComponent, CollisionMode Mode);
		static void SetCollisionChannel(UPrimitiveComponent* PrimitiveComponent, CollisionChannel Channel);
		static void SetCollisionProfileName(UPrimitiveComponent* PrimitiveComponent, const char* ProfileName, bool UpdateOverlaps);
		static void SetCollisionResponseToChannel(UPrimitiveComponent* PrimitiveComponent, CollisionChannel Channel, CollisionResponse Response);
		static void SetCollisionResponseToAllChannels(UPrimitiveComponent* PrimitiveComponent, CollisionResponse Response);
		static void SetIgnoreActorWhenMoving(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, bool Value);
		static void SetIgnoreComponentWhenMoving(UPrimitiveComponent* PrimitiveComponent, UPrimitiveComponent* Component, bool Value);
		static void ClearMoveIgnoreActors(UPrimitiveComponent* PrimitiveComponent);
		static void ClearMoveIgnoreComponents(UPrimitiveComponent* PrimitiveComponent);
		static UMaterialInstanceDynamic* CreateAndSetMaterialInstanceDynamic(UPrimitiveComponent* PrimitiveComponent, int32 ElementIndex);
	}

	namespace ShapeComponent {
		static bool GetDynamicObstacle(UShapeComponent* ShapeComponent);
		static int32 GetShapeColor(UShapeComponent* ShapeComponent);
		static void SetDynamicObstacle(UShapeComponent* ShapeComponent, bool Value);
		static void SetShapeColor(UShapeComponent* ShapeComponent, Color Value);
	}

	namespace BoxComponent {
		static void GetScaledBoxExtent(UBoxComponent* BoxComponent, Vector3* Value);
		static void GetUnscaledBoxExtent(UBoxComponent* BoxComponent, Vector3* Value);
		static void SetBoxExtent(UBoxComponent* BoxComponent, const Vector3* Extent, bool UpdateOverlaps);
		static void InitBoxExtent(UBoxComponent* BoxComponent, const Vector3* Extent);
	}

	namespace SphereComponent {
		static float GetScaledSphereRadius(USphereComponent* SphereComponent);
		static float GetUnscaledSphereRadius(USphereComponent* SphereComponent);
		static float GetShapeScale(USphereComponent* SphereComponent);
		static void SetSphereRadius(USphereComponent* SphereComponent, float SphereRadius, bool UpdateOverlaps);
		static void InitSphereRadius(USphereComponent* SphereComponent, float SphereRadius);
	}

	namespace CapsuleComponent {
		static float GetScaledCapsuleRadius(UCapsuleComponent* CapsuleComponent);
		static float GetUnscaledCapsuleRadius(UCapsuleComponent* CapsuleComponent);
		static float GetShapeScale(UCapsuleComponent* CapsuleComponent);
		static void GetScaledCapsuleSize(UCapsuleComponent* CapsuleComponent, float* Radius, float* HalfHeight);
		static void GetUnscaledCapsuleSize(UCapsuleComponent* CapsuleComponent, float* Radius, float* HalfHeight);
		static void SetCapsuleRadius(UCapsuleComponent* CapsuleComponent, float Radius, bool UpdateOverlaps);
		static void SetCapsuleSize(UCapsuleComponent* CapsuleComponent, float Radius, float HalfHeight, bool UpdateOverlaps);
		static void InitCapsuleSize(UCapsuleComponent* CapsuleComponent, float Radius, float HalfHeight);
	}

	namespace MeshComponent {
		static bool IsValidMaterialSlotName(UMeshComponent* MeshComponent, const char* MaterialSlotName);
		static int32 GetMaterialIndex(UMeshComponent* MeshComponent, const char* MaterialSlotName);
	}

	namespace LightComponentBase {
		static float GetIntensity(ULightComponentBase* LightComponentBase);
		static bool GetCastShadows(ULightComponentBase* LightComponentBase);
		static void SetCastShadows(ULightComponentBase* LightComponentBase, bool Value);
	}

	namespace LightComponent {
		static void SetIntensity(ULightComponent* LightComponent, float Value);
		static void SetLightColor(ULightComponent* LightComponent, const LinearColor* Value);
	}

	namespace DirectionalLightComponent {

	}

	namespace MotionControllerComponent {
		static bool IsTracked(UMotionControllerComponent* MotionControllerComponent);
		static bool GetDisableLowLatencyUpdate(UMotionControllerComponent* MotionControllerComponent);
		static ControllerHand GetTrackingSource(UMotionControllerComponent* MotionControllerComponent);
		static void SetDisableLowLatencyUpdate(UMotionControllerComponent* MotionControllerComponent, bool Value);
		static void SetTrackingSource(UMotionControllerComponent* MotionControllerComponent, ControllerHand Value);
		static void SetTrackingMotionSource(UMotionControllerComponent* MotionControllerComponent, const char* Source);
	}

	namespace StaticMeshComponent {
		static void GetLocalBounds(UStaticMeshComponent* StaticMeshComponent, Vector3* Min, Vector3* Max);
		static UStaticMesh* GetStaticMesh(UStaticMeshComponent* StaticMeshComponent);
		static bool SetStaticMesh(UStaticMeshComponent* StaticMeshComponent, UStaticMesh* StaticMesh);
	}

	namespace InstancedStaticMeshComponent {
		static int32 GetInstanceCount(UInstancedStaticMeshComponent* InstancedStaticMeshComponent);
		static bool GetInstanceTransform(UInstancedStaticMeshComponent* InstancedStaticMeshComponent, int32 InstanceIndex, Transform* Value, bool WorldSpace);
		static int32 AddInstance(UInstancedStaticMeshComponent* InstancedStaticMeshComponent, const Transform* InstanceTransform);
		static bool UpdateInstanceTransform(UInstancedStaticMeshComponent* InstancedStaticMeshComponent, int32 InstanceIndex, const Transform* InstanceTransform, bool WorldSpace, bool MarkRenderStateDirty, bool Teleport);
		static bool RemoveInstance(UInstancedStaticMeshComponent* InstancedStaticMeshComponent, int32 InstanceIndex);
		static void ClearInstances(UInstancedStaticMeshComponent* InstancedStaticMeshComponent);
	}

	namespace SkinnedMeshComponent {
		static void SetSkeletalMesh(USkinnedMeshComponent* SkinnedMeshComponent, USkeletalMesh* SkeletalMesh, bool ReinitializePose);
	}

	namespace SkeletalMeshComponent {
		static bool IsPlaying(USkeletalMeshComponent* SkeletalMeshComponent);
		static UAnimInstance* GetAnimationInstance(USkeletalMeshComponent* SkeletalMeshComponent);
		static void SetAnimation(USkeletalMeshComponent* SkeletalMeshComponent, UAnimationAsset* Asset);
		static void SetAnimationMode(USkeletalMeshComponent* SkeletalMeshComponent, AnimationMode Mode);
		static void SetAnimationBlueprint(USkeletalMeshComponent* SkeletalMeshComponent, UObject* Blueprint);
		static void Play(USkeletalMeshComponent* SkeletalMeshComponent, bool Loop);
		static void PlayAnimation(USkeletalMeshComponent* SkeletalMeshComponent, UAnimationAsset* Asset, bool Loop);
		static void Stop(USkeletalMeshComponent* SkeletalMeshComponent);
	}

	namespace RadialForceComponent {
		static bool GetIgnoreOwningActor(URadialForceComponent* RadialForceComponent);
		static bool GetImpulseVelocityChange(URadialForceComponent* RadialForceComponent);
		static bool GetLinearFalloff(URadialForceComponent* RadialForceComponent);
		static float GetForceStrength(URadialForceComponent* RadialForceComponent);
		static float GetImpulseStrength(URadialForceComponent* RadialForceComponent);
		static float GetRadius(URadialForceComponent* RadialForceComponent);
		static void SetIgnoreOwningActor(URadialForceComponent* RadialForceComponent, bool Value);
		static void SetImpulseVelocityChange(URadialForceComponent* RadialForceComponent, bool Value);
		static void SetLinearFalloff(URadialForceComponent* RadialForceComponent, bool Value);
		static void SetForceStrength(URadialForceComponent* RadialForceComponent, float Value);
		static void SetImpulseStrength(URadialForceComponent* RadialForceComponent, float Value);
		static void SetRadius(URadialForceComponent* RadialForceComponent, float Value);
		static void AddCollisionChannelToAffect(URadialForceComponent* RadialForceComponent, CollisionChannel Channel);
		static void FireImpulse(URadialForceComponent* RadialForceComponent);
	}

	namespace MaterialInterface {
		static bool IsTwoSided(UMaterialInterface* MaterialInterface);
	}

	namespace Material {
		static bool IsDefaultMaterial(UMaterial* Material);
	}

	namespace MaterialInstance {
		static bool IsChildOf(UMaterialInstance* MaterialInstance, UMaterialInterface* Material);
	}

	namespace MaterialInstanceDynamic {
		static void ClearParameterValues(UMaterialInstanceDynamic* MaterialInstanceDynamic);
		static void SetTextureParameterValue(UMaterialInstanceDynamic* MaterialInstanceDynamic, const char* ParameterName, UTexture* Value);
		static void SetVectorParameterValue(UMaterialInstanceDynamic* MaterialInstanceDynamic, const char* ParameterName, const LinearColor* Value);
		static void SetScalarParameterValue(UMaterialInstanceDynamic* MaterialInstanceDynamic, const char* ParameterName, float Value);
	}
}