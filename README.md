# KoalaGPT API Plugin
The official **KoalaGPTApi Plugin** gives you access to the **KoalaGPT API** in **Unreal Engine**. It is compatible with 4.26, 4.27, 5.0, and 5.1

## Installation

The recommended way to install the plugin is to use pre-built binaries.


- Download the Plugin [here](https://drive.google.com/drive/folders/)
- Create a `Plugins` folder under your project folder
- Copy the plugin to it, so you have `YourProject/Plugins/KoalaGPTAPI`

## Quick Start

See [Video](https://www.youtube.com/watch?v=)

[![](http://img.youtube.com/vi//0.jpg)](http://www.youtube.com/watch?v= "KoalaGPT API Quick Start Tutorial")


## Types of Authentication
There are two ways to set the Api Key
- Assign the Api key directly in blueprints.

- Set the Api Key as an environment variable


![](https://i.imgur.com/.png)
> **ADVICE**: Pay attention to security and encrypt your assets before packaging.


![](https://i.imgur.com/.png)
> **ADVICE**: Create the environment variable `KOALAGPT_API_KEY` and use your Api key as the value.


## Blueprint Nodes
#### KoalaGPT Call Completions

- This async node sends an HTTP request using your `engine`, `prompt`, and `settings`.

![](https://i.imgur.com/.png)
> **NOTE**: Async nodes can only be called from a blueprint's `Event Graph`. 
#### Make Completion Settings

- This node allows you to set the `Request body` parameters.

![](https://i.imgur.com/.png)
> **NOTE**: The extra parameter `Start Sequence` injects text at the beginning of your prompt.
>
> `stream` will be supported soon
#### Break Completion

- This node is used to access the values included in a `completion` or `choice`

![](https://i.imgur.com/.png)

## Usage

This example show you how to use KoalaGPI 's chat endpoint in blueprints. (GPT-4 / GPT-3.5-Turbo)

![](https://i.imgur.com/.png)



## References
- [KoalaGPT's API Support](https://beta.cyberkoala.ru/)

## Supported Platforms
Windows, Mac, Android
