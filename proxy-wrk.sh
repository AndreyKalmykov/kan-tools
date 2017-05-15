#!/bin/sh -u

num_args=$#


if [ "$num_args" -ne 2 ]; then
  echo "!!!num_args=$num_args!!!"
  echo "параметры:"
  echo "<Папка/Файл проекта(.xml)>"
  echo "<что сделать> :"
  echo "doProxy - создать прокси(.m2ts) в папке proxy"
  echo "toProxy - заменить в проекте video/*.MTS на proxy/*.m2ts"
  echo "toMTS - заменить в проекте proxy/*.m2ts на video/*.MTS"
  exit 1
fi

p_1=${1}
proj_dir=${p_1%%/*}
proj_file=${p_1##*/}
#~ proj_file_proxy="${proj_file//.xml/-proxy.xml}"
#~ proj_file_MTS="${proj_file//.xml/-MTS.xml}"
proj_file_proxy="${proj_file//.xml/.proxy}"
proj_file_MTS="${proj_file//.xml/.orig}"
proj_video_dir="${proj_dir}/video"
proj_proxy_dir="${proj_dir}/proxy"
to_do=${2}

echo "proj_dir=$proj_dir"
echo "proj_file=$proj_file"
echo "proj_file_proxy=$proj_file_proxy"
echo "to_do=$to_do"
echo

if [ ! -e $proj_dir ]; then
  echo "Нет такого каталога: $proj_dir"
  exit 1
fi
if [ ! -d $proj_dir ]; then
  echo "Это не каталог: $proj_dir"
  exit 1
fi

if [ ! -e "$proj_dir/$proj_file" ]; then
  echo "Отсутствует файл проекта: $proj_file"
  exit 1
fi

    #~ echo "$proj_video_dir"

case "$to_do" in
  "doProxy")
  echo "Создаем прокси файлы в папке proxy..."
  if [ ! -d "$proj_video_dir" ]; then
    echo "!!! В проекте нет каталога video"
    echo "??? $proj_video_dir ???"
    exit 1
  fi
  if [ ! -d "$proj_proxy_dir" ]; then
    echo "Создаем каталог для прокси..."
    echo "$proj_proxy_dir"
    mkdir -p "$proj_proxy_dir"
  fi


  for src_file in ${proj_video_dir}/*.MTS
  do
    src_file="${src_file##*/}"
    proxy_file="${src_file//.MTS/.m2ts}"
    if [ -e "${proj_proxy_dir}/${proxy_file}" ]; then
      continue
    fi
    echo "${src_file} -> ${proxy_file}"
    ffmpeg -hide_banner -i "${proj_video_dir}/${src_file}" -c:v mpeg2video "${proj_proxy_dir}/${proxy_file}"
    #~ exit 0
  done
  exit 0
  ;;
  "toProxy")
  echo "Переводим проект <$proj_file> в режим прокси (.MTS->.m2ts)..."
  n_str=`grep -c '.MTS' "${proj_dir}/${proj_file}"`
  echo $n_str
  if [ "$n_str" -gt 0 ]; then
    cat "${proj_dir}/${proj_file}">"${proj_dir}/${proj_file_MTS}"
    for src_file in ${proj_video_dir}/*.MTS
    do
      src_file="${src_file##*/}"
      proxy_file="${src_file//.MTS/.m2ts}"
      sed -i.bkp -e "s%${proj_video_dir}/${src_file}%${proj_proxy_dir}/${proxy_file}%g;s%${src_file}%${proxy_file}%g" "${proj_dir}/${proj_file}"
    done
  fi
  ;;
  "toMTS")
  echo "Переводим проект <$proj_file> в режим оригинала (.m2ts->.MTS)..."
  n_str=`grep -c '.m2ts' "${proj_dir}/${proj_file}"`
  echo $n_str
  if [ "$n_str" -gt 0 ]; then
    cat "${proj_dir}/${proj_file}">"${proj_dir}/${proj_file_proxy}"
    for src_file in ${proj_video_dir}/*.MTS
    do
      src_file="${src_file##*/}"
      proxy_file="${src_file//.MTS/.m2ts}"
      sed -i.bkp -e "s%${proj_proxy_dir}/${proxy_file}%${proj_video_dir}/${src_file}%g;s%${proxy_file}%${src_file}%g" "${proj_dir}/${proj_file}"
    done
  fi
  ;;
  *)
  echo "??? $to_do ???"
  echo "Команда должна быть одна из: [ doProxy | toProxy | toMTS ]"
  exit 1
esac

exit 0
