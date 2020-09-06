using System;
using System.Drawing;
using UnrealEngine.Framework;

namespace UnrealEngine.Tests {
	public static class Main {
		private static AssertionConsistency assertionConsistency;
		private static AudioPlayback audioPlayback;
		private static BlueprintsExtensibility blueprintsExtensibility;
		private static DebugVisualization debugVisualization;
		private static DynamicEvents dynamicEvents;
		private static DynamicsConsistency dynamicsConsistency;
		private static ExceptionsConsistency exceptionsConsistency;
		private static ExternalConsistency externalConsistency;
		private static InstancedStaticMeshes instancedStaticMeshes;
		private static ObjectOrientedDesign objectOrientedDesign;
		private static PhysicsSimulation physicsSimulation;
		private static RadialForce radialForce;
		private static RuntimeConsistency runtimeConsistency;
		private static SkeletalMeshes skeletalMeshes;
		private static SpatialQueries spatialQueries;
		private static StaticMeshes staticMeshes;
		private static TextureAssets textureAssets;
		private static TestSystems testSystem;
		private static event Action OnBeginPlay;
		private static event Action<float> OnTick;
		private static event Action OnEndPlay;

		public static void OnWorldPostBegin() {
			Debug.Log(LogLevel.Display, "Hello, Unreal Engine!");

			if (World.GetActor<LevelScript>().GetEnum("Test Systems", ref testSystem))
				Debug.AddOnScreenMessage(-1, 3.0f, Color.LightGreen, testSystem + " system started!");

			switch (testSystem) {
				case TestSystems.AssertionConsistency:
					assertionConsistency = new AssertionConsistency();
					OnBeginPlay += assertionConsistency.OnBeginPlay;
					break;

				case TestSystems.AudioPlayback:
					audioPlayback = new AudioPlayback();
					OnBeginPlay += audioPlayback.OnBeginPlay;
					OnEndPlay += audioPlayback.OnEndPlay;
					break;

				case TestSystems.BlueprintsExtensibility:
					blueprintsExtensibility = new BlueprintsExtensibility();
					OnBeginPlay += blueprintsExtensibility.OnBeginPlay;
					OnEndPlay += blueprintsExtensibility.OnEndPlay;
					break;

				case TestSystems.DebugVisualization:
					debugVisualization = new DebugVisualization();
					OnBeginPlay += debugVisualization.OnBeginPlay;
					OnEndPlay += debugVisualization.OnEndPlay;
					break;

				case TestSystems.DynamicEvents:
					dynamicEvents = new DynamicEvents();
					OnBeginPlay += dynamicEvents.OnBeginPlay;
					OnTick += dynamicEvents.OnTick;
					OnEndPlay += dynamicEvents.OnEndPlay;
					break;

				case TestSystems.DynamicsConsistency:
					dynamicsConsistency = new DynamicsConsistency();
					OnBeginPlay += dynamicsConsistency.OnBeginPlay;
					OnTick += dynamicsConsistency.OnTick;
					OnEndPlay += dynamicsConsistency.OnEndPlay;
					break;

				case TestSystems.ExceptionsConsistency:
					exceptionsConsistency = new ExceptionsConsistency();
					OnBeginPlay += exceptionsConsistency.OnBeginPlay;
					OnEndPlay += exceptionsConsistency.OnEndPlay;
					break;

				case TestSystems.ExternalConsistency:
					externalConsistency = new ExternalConsistency();
					OnBeginPlay += externalConsistency.OnBeginPlay;
					break;

				case TestSystems.InstancedStaticMeshes:
					instancedStaticMeshes = new InstancedStaticMeshes();
					OnBeginPlay += instancedStaticMeshes.OnBeginPlay;
					OnTick += instancedStaticMeshes.OnTick;
					OnEndPlay += instancedStaticMeshes.OnEndPlay;
					break;

				case TestSystems.ObjectOrientedDesign:
					objectOrientedDesign = new ObjectOrientedDesign();
					OnBeginPlay += objectOrientedDesign.OnBeginPlay;
					OnTick += objectOrientedDesign.OnTick;
					OnEndPlay += objectOrientedDesign.OnEndPlay;
					break;

				case TestSystems.PhysicsSimulation:
					physicsSimulation = new PhysicsSimulation();
					OnBeginPlay += physicsSimulation.OnBeginPlay;
					OnTick += physicsSimulation.OnTick;
					OnEndPlay += physicsSimulation.OnEndPlay;
					break;

				case TestSystems.RadialForce:
					radialForce = new RadialForce();
					OnBeginPlay += radialForce.OnBeginPlay;
					OnEndPlay += radialForce.OnEndPlay;
					break;

				case TestSystems.RuntimeConsistency:
					runtimeConsistency = new RuntimeConsistency();
					OnBeginPlay += runtimeConsistency.OnBeginPlay;
					break;

				case TestSystems.SkeletalMeshes:
					skeletalMeshes = new SkeletalMeshes();
					OnBeginPlay += skeletalMeshes.OnBeginPlay;
					OnEndPlay += skeletalMeshes.OnEndPlay;
					break;

				case TestSystems.SpatialQueries:
					spatialQueries = new SpatialQueries();
					OnBeginPlay += spatialQueries.OnBeginPlay;
					OnEndPlay += spatialQueries.OnEndPlay;
					break;

				case TestSystems.StaticMeshes:
					staticMeshes = new StaticMeshes();
					OnBeginPlay += staticMeshes.OnBeginPlay;
					OnTick += staticMeshes.OnTick;
					OnEndPlay += staticMeshes.OnEndPlay;
					break;

				case TestSystems.TextureAssets:
					textureAssets = new TextureAssets();
					OnBeginPlay += textureAssets.OnBeginPlay;
					OnEndPlay += textureAssets.OnEndPlay;
					break;

				default:
					break;
			}

			OnBeginPlay?.Invoke();
		}

		public static void OnWorldPrePhysicsTick(float deltaTime) => OnTick?.Invoke(deltaTime);

		public static void OnWorldEnd() {
			OnEndPlay?.Invoke();

			Debug.Log(LogLevel.Display, "See you soon, Unreal Engine!");
		}

		private enum TestSystems {
			AssertionConsistency,
			AudioPlayback,
			BlueprintsExtensibility,
			DebugVisualization,
			DynamicEvents,
			DynamicsConsistency,
			ExceptionsConsistency,
			ExternalConsistency,
			InstancedStaticMeshes,
			ObjectOrientedDesign,
			PhysicsSimulation,
			RadialForce,
			RuntimeConsistency,
			SkeletalMeshes,
			SpatialQueries,
			StaticMeshes,
			TextureAssets
		}
	}
}