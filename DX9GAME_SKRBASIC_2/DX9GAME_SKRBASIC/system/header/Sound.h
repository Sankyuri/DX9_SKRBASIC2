#pragma once
#include "SystemInclude.h"

namespace skrBasic {

	//
	//  音声オブジェクト
	//  DSound のみを用いているので .wav しか使用できません
	//  (Win APIと組み合わせれば何とか出来るらしいけどね……)
	//
	class Sound {
	public:
		//wavファイルをファイルからロード
		//@param a_pSrcFile  .wav ファイルのファイル名
		//@param a_loopStart ループ範囲開始時間(ms)
		//@param a_loopEnd   ループ範囲終了時間(ms)
		HRESULT load(LPCTSTR a_pSrcFile, DWORD a_loopStart = 0L, DWORD a_loopEnd = 0L);

		//wavデータをリソースファイルからロード
		//サンプリングレートはプライマリバッファのものと見做す
		//@param a_pSrcFile  リソースファイルのファイル名
		//@param a_sizeByte  波形データのサイズ [Byte]
		//@param a_offset    波形データ開始迄のオフセット
		//@param a_loopStart ループ範囲開始時間 [ms]
		//@param a_loopEnd   ループ範囲終了時間 [ms]
		HRESULT loadFromResourceFile(LPCTSTR a_pSrcFile, DWORD a_sizeByte, DWORD a_offset,
									 DWORD a_loopStart = 0L, DWORD a_loopEnd = 0L);

		//wavデータをメモリからロード
		//サンプリングレートはプライマリバッファのものと見做す
		//@param a_data      波形データのポインタ
		//@param a_sizeByte  波形データのサイズ [Byte]
		//@param a_offset    波形データ開始迄のオフセット
		//@param a_loopStart ループ範囲開始時間 [ms]
		//@param a_loopEnd   ループ範囲終了時間 [ms]
		HRESULT loadFromMemory(const UCHAR a_data[], DWORD a_sizeByte, DWORD a_offset,
							   DWORD a_loopStart = 0L, DWORD a_loopEnd = 0L);

		
		//音声再生(ループ)
		void playBGM();
		
		//音声再生(単発)
		void playSE();
		
		//音声一時停止
		void pause();
		
		//音声停止
		void stop();


		//音声削除(これを実行した場合、再度読み込むまで再生不可)
		void deleteSound();

		//指定したループスタートでループさせる為の関数。毎フレーム実行させる必要がある
		void checkBGMLoop();


		Sound();
		~Sound();
	private:
		DWORD  dwOffset, dwBlockBytes;
		LPVOID lpvPtr1,  lpvPtr2;
		DWORD  dwBytes1, dwBytes2;
	
		DWORD  playcur,  writecur;

		HMMIO         hMmio;    //所謂FPのようなもの
		MMIOINFO      mmInfo;   //ファイル情報
		MMCKINFO      mmrifck;  //RIFFチャンク情報 ('R', 'I', 'F', 'F')
		MMCKINFO      mmfmtck;  //フォーマットチャンク ('f', 'm', 't', ' ')
		MMCKINFO      mmdatck;  //データチャンク ('d', 'a', 't', 'a')
		WAVEFORMATEX  wavfmtex; //wave ファイル情報
		BYTE         *pData;    //音声データ

		LPDIRECTSOUNDBUFFER8 pDSSecBuf; //セカンダリバッファ

		bool  canPlay;      //再生できるか
		bool  nowPlaying;   //再生中か
		bool  wasBGMLooped; //BGM専用:ループしたか(厳密にはそうじゃ無い)
		bool  useCustomLoop; //ループを特定範囲内で行うか
		DWORD loopStartPos, loopEndPos;    //ループスタート地点、ループエンド地点

		HRESULT dSoundCreateSecondaryBuffer(DWORD rate, float lengthSec); //セカンダリバッファの作成

		HRESULT dSoundLockBuf();   //サウンドバッファのロック
		HRESULT dSoundUnlockBuf(); //サウンドバッファのアンロック

		HRESULT dSoundOpenFile(LPTSTR pSrcFile); //音声ファイルを開く
		HRESULT dSoundLoadToBuf(); //音声ファイルをメモリにロード

		void    setCustomLoop(DWORD loopStart, DWORD loopEnd);


	};

}

