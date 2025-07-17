from PIL import Image

# 读取 PNG 图片
image = Image.open("output_image.png")

# 获取图片大小
width, height = image.size

# 显示图片大小
print(f"图片宽度: {width} 像素")
print(f"图片高度: {height} 像素")