using System;
using System.Drawing;
using System.Numerics;
using System.Reflection;
using UnrealEngine.Framework;

namespace UnrealEngine.Tests {
	public static class SpatialQueries {
		public static void OnBeginPlay() {
			Debug.Log(LogLevel.Display, "Hello, Unreal Engine!");
			Debug.AddOnScreenMessage(-1, 3.0f, Color.LightGreen, MethodBase.GetCurrentMethod().DeclaringType + " system started!");

			World.GetFirstPlayerController().SetViewTarget(World.GetActor<Camera>("MainCamera"));

			const float linesThickness = 3.0f;
			const string collisionProfile = "CollisionProfile";

			Actor box = new Actor("Box");
			StaticMeshComponent staticMeshComponent = new StaticMeshComponent(box, setAsRoot: true);
			Vector3 boxLocation = new Vector3(0.0f, 500.0f, 0.0f);
			Vector3 boxScale = new Vector3(1.0f, 1.0f, 1.0f);

			staticMeshComponent.SetWorldLocation(boxLocation);
			staticMeshComponent.SetWorldScale(boxScale);
			staticMeshComponent.SetStaticMesh(StaticMesh.Cube);
			staticMeshComponent.SetMaterial(0, Material.Load("/Game/Tests/BasicMaterial"));
			staticMeshComponent.CreateAndSetMaterialInstanceDynamic(0).SetVectorParameterValue("Color", new LinearColor(0.18f, 0.0f, 0.9f));
			staticMeshComponent.SetCollisionChannel(CollisionChannel.WorldStatic);
			staticMeshComponent.SetCollisionProfileName(collisionProfile);

			Debug.DrawBox(boxLocation, boxScale * 50.0f, Quaternion.Identity, Color.SlateBlue, true, thickness: linesThickness);

			Hit hit = default(Hit);
			Vector3 lineTraceStart = new Vector3(0.0f, 0.0f, 0.0f);

			bool hitTraceByChannel = World.LineTraceSingleByChannel(lineTraceStart, boxLocation, CollisionChannel.WorldStatic, ref hit);

			Assert.IsTrue(hitTraceByChannel);
			Assert.IsTrue(hit.BlockingHit);

			if (hitTraceByChannel) {
				Debug.AddOnScreenMessage(-1, 15.0f, Color.DeepPink, "Box trace hit by channel!");
				Debug.DrawPoint(hit.TraceStart, 8.0f, Color.DeepPink, true, depthPriority: 3);
				Debug.DrawPoint(hit.TraceEnd, 8.0f, Color.DeepPink, true, depthPriority: 3);
				Debug.DrawLine(hit.TraceStart, hit.TraceEnd, Color.DeepPink, true, depthPriority: 3, thickness: linesThickness);
			}

			bool hitTraceByProfile = World.LineTraceSingleByProfile(lineTraceStart, boxLocation, collisionProfile, ref hit);

			Assert.IsTrue(hitTraceByProfile);
			Assert.IsTrue(hit.BlockingHit);

			if (hitTraceByProfile)
				Debug.AddOnScreenMessage(-1, 15.0f, Color.DeepPink, "Box trace hit by profile!");

			const float sphereRadius = 50.0f;

			CollisionShape sphereShape = CollisionShape.CreateSphere(sphereRadius);

			bool hitSweepByChannel = World.SweepSingleByChannel(lineTraceStart, boxLocation, Quaternion.Identity, CollisionChannel.WorldStatic, sphereShape, ref hit);

			Assert.IsTrue(hitSweepByChannel);
			Assert.IsTrue(hit.BlockingHit);

			if (hitSweepByChannel) {
				Debug.AddOnScreenMessage(-1, 15.0f, Color.Yellow, "Sphere sweep hit by channel!");
				Debug.DrawSphere(hit.Location, sphereRadius, 16, Color.Yellow, true, depthPriority: 2, thickness: linesThickness);
			}

			bool hitSweepByProfile = World.SweepSingleByProfile(lineTraceStart, boxLocation, Quaternion.Identity, collisionProfile, sphereShape, ref hit);

			Assert.IsTrue(hitSweepByProfile);
			Assert.IsTrue(hit.BlockingHit);

			if (hitSweepByProfile)
				Debug.AddOnScreenMessage(-1, 15.0f, Color.Yellow, "Sphere sweep hit by profile!");
		}

		public static void OnEndPlay() {
			Debug.Log(LogLevel.Display, "See you soon, Unreal Engine!");
			Debug.ClearOnScreenMessages();
		}
	}
}