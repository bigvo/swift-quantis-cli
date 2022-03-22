// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "swift-quantis-cli",
    platforms: [
        .macOS(.v12)
    ],
    dependencies: [
        .package(url: "https://github.com/apple/swift-argument-parser", from: "1.1.0"),
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        .target(name: "Quantis", path: "./Sources/Quantis"),
        .executableTarget(name: "SwiftQuantisCLI", dependencies: [
            "Quantis",
            .product(name: "ArgumentParser", package: "swift-argument-parser"),
        ]),

    ]
)
